/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <UIKit/UIKit.h>

#import <ABI44_0_0React/ABI44_0_0RCTComponentViewDescriptor.h>
#import <ABI44_0_0React/ABI44_0_0RCTComponentViewFactory.h>
#import <ABI44_0_0React/ABI44_0_0RCTComponentViewProtocol.h>
#import <ABI44_0_0React/ABI44_0_0renderer/core/ABI44_0_0ReactPrimitives.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Registry of native component views.
 * Provides basic functionality for allocation, recycling, and querying (by tag) native view instances.
 */
@interface ABI44_0_0RCTComponentViewRegistry : NSObject

@property (nonatomic, strong, readonly) ABI44_0_0RCTComponentViewFactory *componentViewFactory;

/**
 * Returns a descriptor referring to a native view instance from the recycle pool (or being created on demand)
 * for given `componentHandle` and with given `tag`.
 * #RefuseSingleUse
 */
- (ABI44_0_0RCTComponentViewDescriptor const &)dequeueComponentViewWithComponentHandle:
                                          (ABI44_0_0facebook::ABI44_0_0React::ComponentHandle)componentHandle
                                                                          tag:(ABI44_0_0facebook::ABI44_0_0React::Tag)tag;

/**
 * Puts a given native component view to the recycle pool.
 * #RefuseSingleUse
 */
- (void)enqueueComponentViewWithComponentHandle:(ABI44_0_0facebook::ABI44_0_0React::ComponentHandle)componentHandle
                                            tag:(ABI44_0_0facebook::ABI44_0_0React::Tag)tag
                        componentViewDescriptor:(ABI44_0_0RCTComponentViewDescriptor)componentViewDescriptor;

/**
 * Returns a component view descriptor by given `tag`.
 */
- (ABI44_0_0RCTComponentViewDescriptor const &)componentViewDescriptorWithTag:(ABI44_0_0facebook::ABI44_0_0React::Tag)tag;

/**
 * Finds a native component view by given `tag`.
 * Returns `nil` if there is no registered component with the `tag`.
 */
- (nullable UIView<ABI44_0_0RCTComponentViewProtocol> *)findComponentViewWithTag:(ABI44_0_0facebook::ABI44_0_0React::Tag)tag;

/**
 * Creates a component view with a given type and puts it to the recycle pool.
 */
- (void)optimisticallyCreateComponentViewWithComponentHandle:(ABI44_0_0facebook::ABI44_0_0React::ComponentHandle)componentHandle;

@end

NS_ASSUME_NONNULL_END
