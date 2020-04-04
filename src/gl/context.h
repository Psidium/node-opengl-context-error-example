#pragma once

#include <napi.h>


class Context: public Napi::ObjectWrap<Context>  {
  public:

    explicit Context(const Napi::CallbackInfo&);
    ~Context();
  
    static void Init(Napi::Env, Napi::Object);
    Napi::Value createContext(const Napi::CallbackInfo& info);
    
 private:
    static Napi::FunctionReference constructor;
};
