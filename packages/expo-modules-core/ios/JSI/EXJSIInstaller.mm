// Copyright 2018-present 650 Industries. All rights reserved.

#import <ExpoModulesCore/EXJSIInstaller.h>
#import <ExpoModulesCore/ExpoModulesHostObject.h>
#import <ExpoModulesCore/Swift.h>

namespace jsi = facebook::jsi;

@interface RCTBridge (ExpoBridgeWithRuntime)

- (void *)runtime;

@end

@implementation EXJavaScriptRuntimeManager

+ (nullable EXJavaScriptRuntime *)runtimeFromBridge:(nonnull RCTBridge *)bridge
{
  jsi::Runtime *jsiRuntime = [bridge respondsToSelector:@selector(runtime)] ? reinterpret_cast<jsi::Runtime *>(bridge.runtime) : nullptr;
  return jsiRuntime ? [[EXJavaScriptRuntime alloc] initWithRuntime:jsiRuntime callInvoker:bridge.jsCallInvoker] : nil;
}

+ (BOOL)installExpoModulesHostObject:(nonnull EXAppContext *)appContext
{
  EXJavaScriptRuntime *runtime = [appContext runtime];

  // The runtime may be unavailable, e.g. remote debugger is enabled or it hasn't been set yet.
  if (!runtime) {
    return false;
  }

  std::shared_ptr<expo::ExpoModulesHostObject> hostObjectPtr = std::make_shared<expo::ExpoModulesHostObject>(appContext);
  EXJavaScriptObject *hostObject = [runtime createHostObject:hostObjectPtr];

  // Define the ExpoModules object as non-configurable, read-only and enumerable property.
  [[runtime global] defineProperty:@"ExpoModules"
                             value:hostObject
                           options:EXJavaScriptObjectPropertyDescriptorEnumerable];
  return true;
}

@end
