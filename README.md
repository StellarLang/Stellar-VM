<img src="./asset/stellar.png" align="right" width="128px" alt="Stellar Icon"/>

# Stellar VM
Stellar VM is the runtime for all Stellar code. It is designed to be portable & embeddable in applications and will be used in the CLI to run compiled & JIT Stellar code.

## Compiling
In order to compile this project you will also need [Stellar-Common]. Similar compilation steps are included in that project.

This project is meant to be consumed as a library. On Linux, run these steps to install the shared library to your system lib and include:

```bash
mkdir build
cmake . -Bcmake-build-debug -G "Unix Makefiles"
cd cmake-build-debug/source
sudo make install
```

## Contributing
Please keep your contributions on-topic and be kind. Contributions of any kind are always welcome!

## License
This project is licensed under the [MIT License](LICENSE).

[Stellar-Common]: https://github.com/StellarLang/Stellar-Common