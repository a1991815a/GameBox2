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
// 		GQuadNode<_Ty>* children[4];		//�ĸ����ӽڵ�
// 	};
// 
// 	GQuadNode<_Ty>*	parent;				//���ڵ�
// 	size_t		depth;				//��ǰ���
// 	_Ty data;						//����
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
// 	//���캯��
// 	GQuadTree();
// 	//��������
// 	GQuadTree(const GQuadTree& tree);
// 	//�ƶ�����
// 	GQuadTree(GQuadTree&& tree);
// 	//��������
// 	~GQuadTree();
// 
// 	//���뺢�ӽڵ㵽�ø��׽ڵ�(���ز���Ľڵ�,���������������ʧ���򷵻ؿ�)
// 	GQuadNode<_Ty>* insert(GQuadNode<_Ty>* parent, const _Ty& ins_data){
// 		GQuadNode<_Ty>* node = alloc();
// 		
// 
// 		return node;
// 	};
// 	//����ڵ�ΪchildIndex������ childIndex: 0~3
// 	GQuadNode<_Ty>* insert(GQuadNode<_Ty>* parent, const _Ty& ins_data, size_t childIndex);
// 	//ɾ���ڵ�(���ظ��׽ڵ�)
// 	GQuadNode<_Ty>* erase(GQuadNode<_Ty>* node){
// 		return dealloc(node);
// 	};
// 	//������нڵ�
// 	void clear();
// 
// 	//���ؽڵ�����
// 	size_t size() const{
// 		return m_uSize;
// 	};
// 	
// 	//����������
// 	size_t depth() const{
// 		return m_uDepth;
// 	};
// 
// 	//���ظ��ڵ�
// 	GQuadNode<_Ty>* root(){
// 		return m_pRoot;
// 	};
// 
// 	//���ظ��ڵ�(������)
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
// 		//�õ����ڵ�
// 		GQuadNode<_Ty>* parent = node->parent;
// 		if(parent)							//������ڵ㲻Ϊ����Ӹ��ڵ�ɾ���ýڵ�
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
// 			for (size_t i = 0; i < 4; ++i)					//��������ӽڵ㵽ջ
// 				stack_node.push_back(node->children[i]);
// 			delete node;
// 			--m_uSize;
// 		}
// 
// 		return parent;
// 	};
// 
// private:
// 	GQuadNode<_Ty>*			m_pRoot;				//���ڵ�
// 	size_t					m_uSize;				//�ڵ����
// 	size_t					m_uDepth;				//������
// };
// 
// #endif