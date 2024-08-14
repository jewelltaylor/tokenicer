from tokenicer.tokenicer import Tokenizer


def test_train_encode_decode():
    train_text = "Here is some example text."
    tokenizer = Tokenizer.train(train_text, vocab_size=260)

    encode_text = "Encode me please. I need to be encoded."
    encoded_ids = tokenizer.encode(encode_text)
    decoded_text = tokenizer.decode(encoded_ids)
    assert encode_text == decoded_text
    tokenizer.free()
