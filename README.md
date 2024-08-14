# TokeniCer 

TokeniCer is a Tokenization library for LLMs written in C with Python bindings that empahsizes simplicity and performance. TokeniCer currently supports [Byte Pair Encoding](https://en.wikipedia.org/wiki/Byte_pair_encoding) tokenization.

🚧 Under active development. 🚧

## Building 
To build the c library that underpins Tokenicer, execute [make](https://www.gnu.org/software/make/) from the root of the repo:
```bash
make
```

## Installing
Optionally, create a virtual environment with your chosen environment management tool. Here [venv](https://docs.python.org/3/library/venv.html) is used:
```bash
python -m venv env_name
source env_name/bin/activate
```

From the root of the repository, install tokenicer as follows:
```bash
pip install .
```

## Usage
A Tokenizer can be initialized by calling the `Tokenizer.train` class method:
```python
# Initialize tokenizer by training on utf-8 encoded text
tokenizer = Tokenizer.train(train_text, vocab_size=40478)

# Given the trained tokenizer, encode some different utf-8 encoded text 
encoded_ids = tokenizer.encode(text_to_encode)

# Given the trained tokenizer, decode some encoded text 
decoded_text = tokenizer.decode(encoded_ids)

```
A Tokenizer can be also be saved to and loaded from disk:
```python
# Initialize tokenizer by training on utf-8 encoded text
tokenizer = Tokenizer.train(train_text, vocab_size=40478)

# Save trained tokenizer to disk
tokenizer.save("filepath.save")

# Load train tokenizer from disk
new_tokenizer = Tokenizer.load("filepath.save")

# Given the trained tokenizer, encode some different utf-8 encoded text 
encoded_ids = new_tokenizer.encode(text_to_encode)

# Given the trained tokenizer, decode some encoded text 
decoded_text = new_tokenizer.decode(encoded_ids)
```

## Roadmap
Features to include:
- [] More seamlessly installation 
- [] Tests for C Code
- [] Memory Leak Check Tests for C Code
- [] Tests for Python Code
- [] Multithreading in C
- [] Benchmarking against [sentencepiece](https://github.com/google/sentencepiece) and [tokenizer](https://huggingface.co/docs/transformers/en/main_classes/tokenizer) 
