WebAssembly Micro Runtime Fork
=========================


This repo is a fork of the [webassembly-micro-runtime](https://github.com/bytecodealliance/wasm-micro-runtime)
repo by bytecodealliance. It includes an additional sample wasm program called "wafle",
which shows how to call a native C function from inside a wasm module.

## Setting up your environment

Clone this repo in your workspace of choice:
```
git clone https://github.com/loloRvz/wasm-micro-runtime.git
cd wasm-micro-runtime

Now follow either of the procedures below
```
### Direct setup

Install the necessary C programming tools:
```
sudo apt-get install gcc build-essential
```

Download the [wasi-sdk](https://github.com/WebAssembly/wasi-sdk/releases)
and extract the archive to its default path ```/opt/wasi-sdk```.
```
curl -L https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz > wasi-sdk.tar.gz
tar xfv wasi-sdk.tar.gz
sudo mv wasi-sdk-12.0 /opt/wasi-sdk
rm wasi-sdk.tar.gz
```

#### Build the sample application

Go to the "wafle" directory and run the build script:
```
cd samples/wafle
./build.sh
```


### Docker-based setup

Build the associated image, including the sample application (wafle):

    make build

and then get a shell with the build:

    make shell

## Running the test

You can now run the program:
```
./out/wafle -f out/wasm-apps/test_com.wasm -a 1
```

The "-f" option specifies the path of the wasm module and the "-a" option
specifies the number of arguments being passed to the wasm module and back.
