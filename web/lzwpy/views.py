"""version interface module. Return database version, database connecting strings and application build version"""

from lzwpy import lzw

lzw_obj = lzw.LZW.getInstance()
    
def encode(params):
    text = str(params['text'])
    """the calculation from C++ library"""
    return {
        # "val" : checkers.findTile(pawn_id)
        'val' : lzw_obj.encodeToString(text)
    }