#define null 0
#pragma once
#include <vector>
#include <queue>

namespace ufl_cap4053 {
	namespace fundamentals {

		template <class T>
		class TreeNode {
		
		private:

			T data;
			std::vector<TreeNode<T>*> children;

		public:
			TreeNode<T>() {
				//Constructor for TreeNode. Should store a default - constructed data value and start with no children.
				TreeNode(null);
			}
			TreeNode<T>(T element) {
				//Constructor for TreeNode. Should store element as its data value and start with no children.
				this->data = element;
				this->children = { };
			}
			const T& getData() const {
				//Returns a reference to the stored data.
				return this->data;
			}
			size_t getChildCount() const {
				//Returns the number of children of this node.
				return children.size();
			}
			TreeNode<T>* getChild(size_t index) {
				//Returns the child node as specified by index.
				return children.at(index);
			}
			TreeNode<T>* getChild(size_t index) const {
				//Returns the child node as specified by index.Note: this is the const version of this method.
				return children.at(index);
			}
			void addChild(TreeNode<T>* child) {
				//Add child to the children of this node.
				children.emplace_back(child);
			}
			TreeNode<T>* removeChild(size_t index) {
				//Remove and return the child node at specified by index. (Note that this does not delete the node!)
				TreeNode* node = children.at(index);
				children.erase(children.begin() + index);
				return node;
			}
			void breadthFirstTraverse(void (*dataFunction)(const T)) const {
				//Breadth - first traversal starting at this node.Calls dataFunction on the element to process it.
				std::queue<TreeNode<T>*> nodes;
				nodes.emplace(this);

				TreeNode<T>* node;
				
				while (!nodes.empty()) {
					node = nodes.front();
					nodes.pop();
					
					dataFunction(node->data);
					
					for (auto& child : node->children) {
						nodes.emplace(child);
					}
				}
			}
			void preOrderTraverse(void (*dataFunction)(const T)) const {
				//Pre - order traversal starting at this node.Calls dataFunction on the element to process it.
				dataFunction(this->data);

				for (auto &child : this->children) {
					child->preOrderTraverse(dataFunction);
				}
			}
			void postOrderTraverse(void (*dataFunction)(const T)) const {
				//Post - order traversal starting at this node.Calls dataFunction on the element to process it.
				for (auto& child : this->children) {
					child->postOrderTraverse(dataFunction);
				}

				dataFunction(this->data);
			}
		};
	};
};