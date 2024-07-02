class CRC16:
    def __init__(self, poly, init, ref_in, ref_out, xor_out):
        self.poly = poly
        self.init = init
        self.ref_in = ref_in
        self.ref_out = ref_out
        self.xor_out = xor_out
        self.mask = 0xFFFF

    def reflect(self, data, bits):
        reflection = 0
        for bit in range(bits):
            if data & (1 << bit):
                reflection |= (1 << (bits - 1 - bit))
        return reflection

    def generate_table(self):
        table = []
        for byte in range(256):
            crc = byte << 8 if not self.ref_in else self.reflect(byte, 8) << 8
            for _ in range(8):
                if crc & 0x8000:
                    crc = (crc << 1) ^ self.poly
                else:
                    crc <<= 1
            if self.ref_out:
                crc = self.reflect(crc >> 8, 8)
            table.append(crc & 0xFFFF)
        return table

# CRC-16 variants and their parameters
crc_variants = {
    "CRC-16/ARC":         CRC16(poly=0x8005, init=0x0000, ref_in=True,  ref_out=True,  xor_out=0x0000),
    "CRC-16/AUG-CCITT":   CRC16(poly=0x1021, init=0x1D0F, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/BUYPASS":     CRC16(poly=0x8005, init=0x0000, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/CCITT-FALSE": CRC16(poly=0x1021, init=0xFFFF, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/CDMA2000":    CRC16(poly=0xC867, init=0xFFFF, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/DDS-110":     CRC16(poly=0x8005, init=0x800D, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/DECT-R":      CRC16(poly=0x0589, init=0x0000, ref_in=False, ref_out=False, xor_out=0x0001),
    "CRC-16/DECT-X":      CRC16(poly=0x0589, init=0x0000, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/DNP":         CRC16(poly=0x3D65, init=0x0000, ref_in=True,  ref_out=True,  xor_out=0xFFFF),
    "CRC-16/EN-13757":    CRC16(poly=0x3D65, init=0x0000, ref_in=False, ref_out=False, xor_out=0xFFFF),
    "CRC-16/GENIBUS":     CRC16(poly=0x1021, init=0xFFFF, ref_in=False, ref_out=False, xor_out=0xFFFF),
    "CRC-16/KERMIT":      CRC16(poly=0x1021, init=0x0000, ref_in=True,  ref_out=True,  xor_out=0x0000),
    "CRC-16/MAXIM":       CRC16(poly=0x8005, init=0x0000, ref_in=True,  ref_out=True,  xor_out=0xFFFF),
    "CRC-16/MCRF4XX":     CRC16(poly=0x1021, init=0xFFFF, ref_in=True,  ref_out=True,  xor_out=0x0000),
    "CRC-16/MODBUS":      CRC16(poly=0x8005, init=0xFFFF, ref_in=True,  ref_out=True,  xor_out=0x0000),
    "CRC-16/RIELLO":      CRC16(poly=0x1021, init=0xB2AA, ref_in=True,  ref_out=True,  xor_out=0x0000),
    "CRC-16/T10-DIF":     CRC16(poly=0x8BB7, init=0x0000, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/TELEDISK":    CRC16(poly=0xA097, init=0x0000, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-16/TMS37157":    CRC16(poly=0x1021, init=0x89EC, ref_in=True,  ref_out=True,  xor_out=0x0000),
    "CRC-16/USB":         CRC16(poly=0x8005, init=0xFFFF, ref_in=True,  ref_out=True,  xor_out=0xFFFF),
    "CRC-16/X-25":        CRC16(poly=0x1021, init=0xFFFF, ref_in=True,  ref_out=True,  xor_out=0xFFFF),
    "CRC-16/XMODEM":      CRC16(poly=0x1021, init=0x0000, ref_in=False, ref_out=False, xor_out=0x0000),
    "CRC-A":              CRC16(poly=0x1021, init=0xC6C6, ref_in=True,  ref_out=True,  xor_out=0x0000),
}

# Generate and print the lookup tables for all configurations
for name, crc_calculator in crc_variants.items():
    table = crc_calculator.generate_table()
    print(f"// Lookup table for {name}")
    print(f"const uint16_t crc16_{name.lower().replace('-', '_').replace('/', '_')}_table[256] = {{")
    for i in range(0, 256, 8):
        row = ", ".join(f"0x{value:04X}" for value in table[i:i+8])
        print(f"    {row},")
    print("};\n")
