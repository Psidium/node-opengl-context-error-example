# node-opengl-context-error-example
This repository is an example for anyone looking how NOT to create an OpenGL context in an NodeJS native addon.

# Install

To install it, ensure you have `make`, `cmake` and `node` installed on your machine.

```bash
yarn global add cmake-js # OR npm install -g cmake-js
yarn install
cmake-js build
```

# Running

To run it, simply execute 
```bash
node run.js
```

The OpenGL context will be created successfullyy if you see a message like:

```
: Current context currently is: 0xafafafafaf0102f0af8afa
```

If you find an error when creating the context (most likely will), you will see something like:
```
undefined: Error returned by choosePixelFormat: 10017
```
