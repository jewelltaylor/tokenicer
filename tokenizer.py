import ctypes
from ctypes import c_char_p, c_long, c_void_p, POINTER, byref

libtokenizer = ctypes.CDLL("./lib/libtokenizer.so")

libtokenizer.tokenizer_train.argtypes = [c_char_p, c_long]
libtokenizer.tokenizer_train.restype = c_void_p

libtokenizer.tokenizer_encode.argtypes = [c_void_p, c_char_p, POINTER(c_long)]
libtokenizer.tokenizer_encode.restype = POINTER(c_long)

libtokenizer.tokenizer_decode.argtypes = [c_void_p, POINTER(c_long), c_long]
libtokenizer.tokenizer_decode.restype = c_char_p

libtokenizer.tokenizer_save.argtypes = [c_void_p, c_char_p]
libtokenizer.tokenizer_save.restype = None

libtokenizer.tokenizer_load.argtypes = [c_char_p]
libtokenizer.tokenizer_load.restype = c_void_p

libtokenizer.tokenizer_free.argtypes = [c_void_p]
libtokenizer.tokenizer_free.restype = None

libtokenizer.tokenizer_free_array.argtypes = [POINTER(c_long), c_long]
libtokenizer.tokenizer_free_array.restype = None


class Tokenizer:
    def __init__(self, tokenizer_ptr):
        if not tokenizer_ptr:
            raise ValueError("Invalid Tokenizer Pointer")

        self.tokenizer = tokenizer_ptr

    @classmethod
    def train(cls, text, vocab_size):
        tokenizer_ptr = libtokenizer.tokenizer_train(
            text.encode("utf-8"), vocab_size)
        return cls(tokenizer_ptr=tokenizer_ptr)

    @classmethod
    def load(cls, filepath):
        tokenizer_ptr = libtokenizer.tokenizer_load(filepath.encode("utf-8"))
        return cls(tokenizer_ptr=tokenizer_ptr)

    def encode(self, text):
        ids_array_length = c_long()
        encoded_ptr = libtokenizer.tokenizer_encode(
            self.tokenizer, text.encode("utf-8"), byref(ids_array_length))
        encoded_ids = [encoded_ptr[i] for i in range(ids_array_length.value)]
        libtokenizer.tokenizer_free_array(encoded_ptr, ids_array_length.value)
        return encoded_ids

    def decode(self, ids):
        array_type = c_long * len(ids)
        c_array = array_type(*ids)
        decoded_cstr = libtokenizer.tokenizer_decode(
            self.tokenizer, c_array, c_long(len(ids)))
        return ctypes.string_at(decoded_cstr).decode('utf-8')

    def save(self, filepath):
        libtokenizer.tokenizer_save(self.tokenizer, filepath.encode("utf-8"))

    def free(self):
        if self.tokenizer:
            libtokenizer.tokenizer_free(self.tokenizer)
            self.tokenizer = None

    def __del__(self):
        self.free()
