//
// Created by 11706 on 2021/7/14.
//
#ifndef BEHAVIOR_TREE__NODE_H_
#define BEHAVIOR_TREE__NODE_H_

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <memory>

///!
std::string attack_flag{"attack2"};
std::string defend_flag{"defend2"};

class BehaviorNode {
 public:

  typedef std::shared_ptr<BehaviorNode> Ptr;
  /**
   * @brief Constructor of BehaviorNode
   * @param name Name of the behavior node
   */
  explicit BehaviorNode(std::string name) {
    name_ = std::move(name);
  }
  ///! 默认析构函数
  virtual ~BehaviorNode() = default;
  ///! 执行函数
  virtual void Run() = 0;
  ///! 添加一个子节点
  virtual void AddChildren(const BehaviorNode::Ptr &child_node_ptr) {
    children_.push_back(child_node_ptr);
  }
  ///! 添加一些子节点
  virtual void AddChildren(std::initializer_list<BehaviorNode::Ptr> child_node_ptr_list) {
    for (const auto &child : child_node_ptr_list) {
      children_.push_back(child);
    }
  }
  ///! 是否可以执行该节点
  virtual bool CanRun() {
    return true;
  }

  std::string GetName() {
    return name_;
  }

 private:

  std::string name_;

 protected:

  std::vector<BehaviorNode::Ptr> children_{};

};

class ActionNode : public BehaviorNode {
 public:
  /**
   * @brief Constructor of ActionNode
   * @param name Name of the Action node
   */
  explicit ActionNode(std::string name) : BehaviorNode::BehaviorNode(std::move(name)) {

  }

  ~ActionNode() override = default;

  void Run() override {
    std::cout << BehaviorNode::GetName() << " is running" << std::endl;
  }

  bool CanRun() override {
    if (BehaviorNode::GetName() == attack_flag or BehaviorNode::GetName() == defend_flag) {
      return true;
    }
    return false;
  }
};

class SelectorNode : public BehaviorNode {
 public:
  /**
   * @brief Constructor of SelectorNode
   * @param name Name of the Select node
   */
  explicit SelectorNode(const std::string &name) : BehaviorNode(name) {

  }

  ~SelectorNode() override = default;

  void Run() override {
    for (const auto &child : children_) {
      if (child->CanRun()) {
        child->Run();
        break;
      }
    }
  }

};

class ParallelNode : public BehaviorNode {
 public:
  /**
   * @brief Constructor of ParallelNode
   * @param name Name of the Parallel node
   */
  explicit ParallelNode(const std::string &name) : BehaviorNode(name) {

  }

  ~ParallelNode() override = default;

  void Run() override {
    for (const auto &child : children_) {
      child->Run();
    }
  }

};

#endif //BEHAVIOR_TREE__NODE_H_
