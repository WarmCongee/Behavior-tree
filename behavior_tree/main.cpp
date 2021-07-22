#include "node.h"

int main() {
  ///! 初始化根节点
  BehaviorNode::Ptr root = std::make_shared<ParallelNode>("root");
  ///! 初始化选择节点
  BehaviorNode::Ptr attack_select_node = std::make_shared<SelectorNode>("attack_select");
  BehaviorNode::Ptr defend_select_node = std::make_shared<SelectorNode>("defend_select");
  ///! 初始化进攻节点
  BehaviorNode::Ptr attack_node1 = std::make_shared<ActionNode>("attack1");
  BehaviorNode::Ptr attack_node2 = std::make_shared<ActionNode>("attack2");
  ///! 初始化防御节点
  BehaviorNode::Ptr defend_node1 = std::make_shared<ActionNode>("defend1");
  BehaviorNode::Ptr defend_node2 = std::make_shared<ActionNode>("defend2");
  ///! 连接根节点与两个选择节点
  root->AddChildren({attack_select_node, defend_select_node});
  ///! 分别连接两个选择节点与子动作节点
  attack_select_node->AddChildren({attack_node1, attack_node2});
  defend_select_node->AddChildren({defend_node1, defend_node2});

  root->Run();
}