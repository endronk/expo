/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ABI44_0_0AndroidSwitchMeasurementsManager.h"

#include <ABI44_0_0React/ABI44_0_0renderer/components/rncore/EventEmitters.h>
#include <ABI44_0_0React/ABI44_0_0renderer/components/rncore/Props.h>
#include <ABI44_0_0React/ABI44_0_0renderer/components/view/ConcreteViewShadowNode.h>

namespace ABI44_0_0facebook {
namespace ABI44_0_0React {

extern const char AndroidSwitchComponentName[];

/*
 * `ShadowNode` for <AndroidSwitch> component.
 */
class AndroidSwitchShadowNode final : public ConcreteViewShadowNode<
                                          AndroidSwitchComponentName,
                                          AndroidSwitchProps,
                                          AndroidSwitchEventEmitter> {
 public:
  using ConcreteViewShadowNode::ConcreteViewShadowNode;

  // Associates a shared `AndroidSwitchMeasurementsManager` with the node.
  void setAndroidSwitchMeasurementsManager(
      const std::shared_ptr<AndroidSwitchMeasurementsManager>
          &measurementsManager);

#pragma mark - LayoutableShadowNode

  Size measureContent(
      LayoutContext const &layoutContext,
      LayoutConstraints const &layoutConstraints) const override;

 private:
  std::shared_ptr<AndroidSwitchMeasurementsManager> measurementsManager_;
};

} // namespace ABI44_0_0React
} // namespace ABI44_0_0facebook
