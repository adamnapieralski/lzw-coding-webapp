from lzwpy import lzw

lzw_obj = lzw.LZW()
    
def encode(params):
    text = str(params['text'])
    return {
        'code' : lzw_obj.encodeToString(text)
    }

def decode(params):
    text = str(params['text'])
    return {
        'text' : lzw_obj.decodeFromString(text)
    }

def changeBitSize(params):
    global lzw_obj
    bitSize = int(params['bitSize'])
    lzw_obj = lzw.LZW(bitSize)

def getCompressionRate(params):
    return {
        'CR' : lzw_obj.getCompressionRate()
    }