# XOR encryption

A very not user friendly encryption utility that basically destroys the data if you supply the wrong password.

run `make` to see the action, `sh reset.sh`to reset the `list.txt` file for testing.

Usage: `./main < file to encrypt/decrypt > < password >`

## Usage

* `./main < file to encrypt/decrypt >` -- uses default key? or previous char (icebox) -- outputs to standard out
* `./main < file to encrypt/decrypt > -p/--password < password to use as a key>`
* `./main < file to encrypt/decrypt > -o/--out < file to output too >`
* `./main < file to encrypt/decrypt > -k/--key < file that contains key to use >`
* `./main -h/--help` displays help

## Todo list

* [x] Write file
* [ ] add flags
	* [ ] read password from file
	* [ ] generate password
	* [ ] reference self (previous char) instead of password
* [x] display output and prompt prior to writing file
* [ ] add help
* [ ] figure out a good way to do binary in/out
	* maybe have a flag that is placed at the start of the binary file? 

