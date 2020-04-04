#include "context.h"

#include <iostream>
#include <OpenGL/OpenGL.h>

Context::Context(const Napi::CallbackInfo& info): Napi::ObjectWrap<Context>(info) {

}

Context::~Context() {

}
Napi::FunctionReference Context::constructor;

void Context::Init(Napi::Env env, Napi::Object exports) {
    auto func = DefineClass(env, "OpenglContext", {
        InstanceMethod("createContext", &Context::createContext)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("OpenglContext", func);
    return (void) exports;
}

Napi::Value Context::createContext(const Napi::CallbackInfo& info) {
    std::string printIdentifier = ""; // Use this to debug

    CGLContextObj context;
    CGLPixelFormatAttribute attributes[2] = {
            kCGLPFAAccelerated,   // no software rendering
            (CGLPixelFormatAttribute) 0
    };

    CGLPixelFormatObj pix;
    CGLError errorCode;
    GLint num; // stores the number of possible pixel formats
    errorCode = CGLChoosePixelFormat( attributes, &pix, &num );
    if (errorCode > 0) {
      std::cout << printIdentifier << ": Error returned by choosePixelFormat: " << errorCode << "\n";
      return info.Env().Undefined();
    }
    // add error checking here
    errorCode = CGLCreateContext( pix, NULL, &context );
    if (errorCode > 0) {
      std::cout << printIdentifier << ": Error returned by CGLCreateContext: " << errorCode << "\n";
      return info.Env().Undefined();
    }
    // add error checking here
    CGLDestroyPixelFormat( pix );

    errorCode = CGLSetCurrentContext( context );
    if (errorCode > 0) {
      std::cout << printIdentifier << ": Error returned by CGLSetCurrentContext: " << errorCode << "\n";
      return info.Env().Undefined();
    }

    std::cout << printIdentifier << ": Current context currently is: " << CGLGetCurrentContext() << "\n";
      return info.Env().Undefined();
}
