// #ifndef __GQUADTREE__
// #define __GQUADTREE__
// #include <vector>
// #include <stdexcept>
// 
// template<typename _Ty>
// class GQuadNode {
// 	class template<typename> GQuadTree<_Ty>;
// public:
// 
// 
// 
// private:
// 	union
// 	{
// 		struct{
// 			GQuadNode<_Ty>* child1, child2, child3, child4;
// 		};
// 		GQuadNode<_Ty>* children[4];		//四个孩子节点
// 	};
// 
// 	GQuadNode<_Ty>*	parent;				//父节点
// 	size_t		depth;				//当前深度
// 	_Ty data;						//数据
// };
// 
// template<typename _Ty>
// class GQuadTree{
// public:
// 	typedef _Ty					value_type;
// 	typedef _Ty*				pointer;
// 	typedef const _Ty*			const_pointer;
// 	typedef _Ty&				reference;GQuadNode
// 	typedef const _Ty&			const_reference;
// 	typedef size_t				size_type;
// 	typedef	size_t				difference_type;
// public:
// 	//构造函数
// 	GQuadTree();
// 	//拷贝构造
// 	GQuadTree(const GQuadTree& tree);
// 	//移动构造
// 	GQuadTree(GQuadTree&& tree);
// 	//析构函数
// 	~GQuadTree();
// 
// 	//插入孩子节点到该父亲节点(返回插入的节点,如果孩子已满插入失败则返回空)
// 	GQuadNode<_Ty>* insert(GQuadNode<_Ty>* parent, const _Ty& ins_data){
// 		GQuadNode<_Ty>* node = alloc();
// 		
// 
// 		return node;
// 	};
// 	//插入节点为childIndex个孩子 childIndex: 0~3
// 	GQuadNode<_Ty>* insert(GQuadNode<_Ty>* parent, const _Ty& ins_data, size_t childIndex);
// 	//删除节点(返回父亲节点)
// 	GQuadNode<_Ty>* erase(GQuadNode<_Ty>* node){
// 		return dealloc(node);
// 	};
// 	//清空所有节点
// 	void clear();
// 
// 	//返回节点总数
// 	size_t size() const{
// 		return m_uSize;
// 	};
// 	
// 	//返回最大深度
// 	size_t depth() const{
// 		return m_uDepth;
// 	};
// 
// 	//返回根节点
// 	GQuadNode<_Ty>* root(){
// 		return m_pRoot;
// 	};
// 
// 	//返回根节点(常量版)
// 	const GQuadNode<_Ty>* root() const{
// 		return m_pRoot;
// 	}
// 
// private:
// 	GQuadNode<_Ty>* alloc(){
// 		++m_uSize;
// 		return new GQuadNode<_Ty>();
// 	};
// 	GQuadNode<_Ty>* dealloc(GQuadNode<_Ty>* node){
// 		if(node == nullptr)
// 			return nullptr;
// 
// 		//得到父节点
// 		GQuadNode<_Ty>* parent = node->parent;
// 		if(parent)							//如果父节点不为空则从父节点删除该节点
// 		{
// 			for (size_t i = 0; i < 4; ++i)
// 			{
// 				if(node == parent->children[i])
// 				{
// 					parent->children[i] = nullptr;
// 					break;
// 				}
// 			}
// 		}
// 
// 		std::vector<GQuadNode<_Ty>*> stack_node;
// 		stack_node.push_back(node);
// 
// 		while (!stack_node.empty())
// 		{
// 			GQuadNode<_Ty>* node = stack_node.back();
// 			stack_node.pop_back();
// 			if(node == nullptr)
// 				continue;
// 			for (size_t i = 0; i < 4; ++i)					//遍历添加子节点到栈
// 				stack_node.push_back(node->children[i]);
// 			delete node;
// 			--m_uSize;
// 		}
// 
// 		return parent;
// 	};
// 
// private:
// 	GQuadNode<_Ty>*			m_pRoot;				//根节点
// 	size_t					m_uSize;				//节点个数
// 	size_t					m_uDepth;				//最大深度
// };
// 
// #endif