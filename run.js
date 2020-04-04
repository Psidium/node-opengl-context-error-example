function loadLib() {
    try {
        return require("./build/Release/opengl-context.node");
    } catch (e) {
    try {
        return  require("./build/Release/Debug/opengl-context.node");
    } catch (e) {
        return  require("./build/Release/Release/opengl-context.node");
    }
    }
}
const { OpenglContext } = loadLib();

const ctx = new OpenglContext();

ctx.createContext();
