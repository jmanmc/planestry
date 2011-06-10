#pragma once
#include <vector>
#include <string>

namespace scx
{
	template <typename NodeType>
	class SceneNode
	{
		public:
			SceneNode(std::string name) : Name(name) {};
			~SceneNode() {};

			std::string GetName() { return Name; };
			std::vector<NodeType*> Children;

		private:
			std::string Name;
			
	};
	
	template <typename NodeType>
	class SceneGraph
	{
		public:
			SceneGraph(NodeType* Root = NULL) : RootNode(Root) {};
			~SceneGraph() {};

			void DrawNodes()
			{

				if(RootNode == NULL)
					return;

				for(int i = 0; i < RootNode->Children.size(); ++i)
				{
					RootNode->Children[i]->Update();
					RootNode->Children[i]->Draw();
					//NodeType *CurrentNode = &RootNode->Children[i];

					for(int a = 0; a < RootNode->Children[i]->Children.size(); ++a)
					{
						RootNode->Children[i]->Update();
						RootNode->Children[i]->Children[a]->Draw();
					}
				}
			}

			void Add(NodeType* Node, NodeType* Parent = NULL)
			{
				if(Parent == NULL)
					if(RootNode != NULL)
						Parent = RootNode;
					else
						return;

				Parent->Children.push_back(Node);
			}

			NodeType& Find(std::string name)
			{
				if(RootNode == NULL)
					return NodeType("");

				if(!name.compare(RootNode->GetName()))
					return (*RootNode);


			}
			
		private:
			NodeType *RootNode;
	};
			
}