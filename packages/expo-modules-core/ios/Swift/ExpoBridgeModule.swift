// Copyright 2022-present 650 Industries. All rights reserved.

import React
import Foundation

@objc(ExpoBridgeModule)
public final class ExpoBridgeModule: NSObject, RCTBridgeModule {
  @objc
  public let appContext: AppContext

  /**
   The initializer used by React Native when it loads bridge modules.
   In this scenario, we create an `AppContext` that manages the
   architecture of Expo modules and the app itself.
   */
  override init() {
    appContext = AppContext().useModulesProvider("ExpoModulesProvider")
    super.init()
  }

  // MARK: - RCTBridgeModule

  public static func moduleName() -> String! {
    return "Expo"
  }

  public static func requiresMainQueueSetup() -> Bool {
    return true
  }

  public var bridge: RCTBridge! {
    didSet {
      appContext.reactBridge = bridge
    }
  }

  public func constantsToExport() -> [AnyHashable: Any]! {
    // Install ExpoModules host object in the runtime. It's probably not the right place,
    // but it's the earliest moment in bridge's lifecycle when we have access to the runtime.
    try? appContext.installExpoModulesHostObject()

    return [:]
  }
}
