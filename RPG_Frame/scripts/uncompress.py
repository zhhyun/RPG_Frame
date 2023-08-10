import base64
import zlib
import struct
def UncompressFc(basezipstr : str, width, height):
    basezipout = base64.b64decode(basezipstr)
    decompressed = zlib.decompress(basezipout)
    size = width * height
    strr = str(size) + 'i'
    datax = struct.unpack(strr, decompressed)
    return datax 