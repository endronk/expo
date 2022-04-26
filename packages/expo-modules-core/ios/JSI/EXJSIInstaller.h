// Copyright 2018-present 650 Industries. All rights reserved.

@class EXAppContext;

@interface EXJavaScriptRuntimeManager : NSObject

/**
 Installs ExpoModules host object in the runtime of the given app context.
 Returns a bool value whether the installation succeeded.
 */
+ (BOOL)installExpoModulesHostObject:(nonnull EXAppContext *)appContext;

@end
