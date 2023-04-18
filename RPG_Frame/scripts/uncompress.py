import base64
import zlib
import struct
def UncompressFc(basezipstr : str):
    basezipout = base64.b64decode(basezipstr)
    decompressed = zlib.decompress(basezipout)
    datax = struct.unpack('936i', decompressed)
    return datax