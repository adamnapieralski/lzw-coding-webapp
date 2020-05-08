from lzwpy import lzw

lzw_obj = lzw.LZW.getInstance()
    
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
    bitSize = int(params['bitSize'])
    lzw_obj.setBitSize(bitSize)

def getCompressionRate(params):
    return {
        'CR' : lzw_obj.getCompressionRate()
    }