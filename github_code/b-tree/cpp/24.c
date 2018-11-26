#include <time.h>
#include "MyBiTree.h"

/*
A
B       C
D   E       F
G
*/
#if 0
void
test_basic(void)
{
    CMyBiTree tree;
    
#if 0
    CTreeNode *pNode1 = tree.Insert('A', NULL, true);
    CTreeNode *pNode2 = tree.Insert('B', pNode1, true);
    CTreeNode *pNode3 = tree.Insert('D', pNode2, true);
    CTreeNode *pNode4 = tree.Insert('E', pNode2, false);
    CTreeNode *pNode5 = tree.Insert('G', pNode4, true);
    CTreeNode *pNode6 = tree.Insert('C', pNode1, false);
    CTreeNode *pNode7 = tree.Insert('F', pNode6, false);
#endif
    
    //tree.PreOrder(tree.GetRoot());
    tree.MidOrder(tree.GetRoot());
    //tree.PostOrder(tree.GetRoot());
    cout << endl;
    
    //tree.PreOrder_Non(tree.GetRoot());
    cout << endl;
    
    //tree.MidOrder_Non(tree.GetRoot());
}

void 
test_sorted(void)
{
    CMyBiTree tree;

    //30,11,18,4,55,29,15,70,58
    tree.Insert(30);
    tree.Insert(11);
    tree.Insert(18);
    tree.Insert(4);
    tree.Insert(55);
    tree.Insert(29);
    tree.Insert(15);
    tree.Insert(70);
    tree.Insert(58);

    tree.MidOrder(tree.GetRoot());
    cout << endl;

    const CTreeNode *pNode = tree.Find(1);
    if (pNode != NULL)
    {
        cout << "Found" << endl;
    }

#if 0 // ɾ��Ҷ�ӽ��
    tree.Remove(tree.Find(4));
    tree.Remove(tree.Find(15));
    tree.Remove(tree.Find(19));
    tree.Remove(tree.Find(58));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
#endif

#if 0   //ɾ������һ���ӽ��Ľ��
    tree.Remove(tree.Find(55));
    tree.Remove(tree.Find(70));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
#endif

#if 1
    //ɾ���������ӽ��Ľ��
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    //tree.Remove(tree.Find(11));
    tree.Remove(tree.Find(18));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
#endif

#if 0
    tree.Insert(18);
    tree.MidOrder(tree.GetRoot());
    cout << endl;

    tree.Modify(tree.Find(18), 19);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
#endif
}

void
test_remove(void)
{
    CMyBiTree tree;
    
    tree.Insert(31);
    tree.Insert(39);
    tree.Insert(35);
    tree.Insert(70);
    tree.Insert(33);
    tree.Insert(36);
    tree.Insert(89);
    tree.Insert(38);
    tree.Insert(37);
    
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(39));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(38));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(37));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(36));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(35));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(33));
    tree.MidOrder(tree.GetRoot());
    cout << endl;

}

void
test_AVL_BF(void)
{
    CMyBiTree tree;
    tree.Insert(10);
    tree.LevelWalk(tree.GetRoot());
    tree.Insert(15);
    tree.LevelWalk(tree.GetRoot());
    tree.Insert(13);
    tree.LevelWalk(tree.GetRoot());
    tree.Insert(14);
    tree.LevelWalk(tree.GetRoot());
    tree.Insert(18);
    tree.LevelWalk(tree.GetRoot());
    tree.Insert(19);
    tree.LevelWalk(tree.GetRoot());
    cout << endl;
    tree.Insert(20);
    tree.LevelWalk(tree.GetRoot());
    cout << endl;

    tree.Remove(tree.Find(19));
    tree.LevelWalk(tree.GetRoot());

}

void
test_AVL_BF_1(void)
{
    CMyBiTree tree;
    
    tree.Insert(31);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(39);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(35);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(70);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(33);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(36);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(89);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(38);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Insert(37);
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    /////////////////////
    
    tree.Remove(tree.Find(33));
    tree.MidOrder(tree.GetRoot());
    cout << endl;

    tree.Remove(tree.Find(39));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(38));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(37));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(36));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(35));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(33));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(31));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(70));
    tree.MidOrder(tree.GetRoot());
    cout << endl;
    
    tree.Remove(tree.Find(89));
    tree.MidOrder(tree.GetRoot());
    cout << endl;

}

void
test_AVL_ROTATE_SINGLE_LEFT(void)
{
    //rotatesingleleft
    CMyBiTree tree;

    tree.Insert(10);
    tree.Insert(15);
    tree.Insert(16);

    tree.MidOrder(tree.GetRoot());
    cout << endl;

    CMyBiTree tree1;
    tree1.Insert(50);
    tree1.Insert(45);
    tree1.Insert(55);
    tree1.Insert(40);
    tree1.Insert(53);
    tree1.Insert(60);
    tree1.Insert(58);
    tree1.Insert(65);

    tree1.MidOrder(tree1.GetRoot());
    cout << endl;

    tree1.Insert(63);
    tree1.MidOrder(tree1.GetRoot());
   cout << endl;
}

void
test_AVL_ROTATE_SINGLE_RIGHT(void)
{
    CMyBiTree tree;

    tree.Insert(10);
    tree.Insert(8);
    tree.Insert(6);

    tree.MidOrder(tree.GetRoot());
    cout << endl;

    /// 
    CMyBiTree tree1;
    tree1.Insert(50);
    tree1.Insert(45);
    tree1.Insert(55);
    tree1.Insert(40);
    tree1.Insert(48);
    tree1.Insert(60);
    tree1.Insert(35);
    tree1.Insert(43);
    
    tree1.MidOrder(tree1.GetRoot());
    cout << endl;
    
    tree1.Insert(33);
    tree1.MidOrder(tree1.GetRoot());
    cout << endl;
}

void
test_AVL_ROTATE_DOUBLE_LEFT(void)
{
    CMyBiTree tree;

    tree.Insert(10);
    tree.Insert(6);
    tree.Insert(8);

    tree.MidOrder(tree.GetRoot());
}

void
test_AVL_ROTATE_DOUBLE_RIGHT(void)
{
    CMyBiTree tree;
    tree.Insert(10);
    tree.Insert(13);
    tree.Insert(12);

    tree.MidOrder(tree.GetRoot());
}

void
test_ROTATE_INSERT(void)
{
    CMyBiTree tree;

    int num = 100000;
    int i = 0, j;
    srand((unsigned)time(NULL));
    while(tree.GetCount() != num)
    {
        j = (rand() % num) * (rand() % num);

        tree.Insert(j);
    }

    cout << tree.GetCount() << endl;   
    cout << "Goint to Remove" << endl;
    getchar();

    while (tree.GetCount()!= 0)
    {
        j = (rand() % num) * (rand() % num);

        if (tree.GetCount() % 10000 == 0)
        {
            cout << tree.GetCount() << endl;
        }

        tree.Remove(tree.Find(j));
    }

    cout << tree.GetCount() << endl;
    tree.MidOrder(tree.GetRoot());

}

int
test_main(void)
{
    //test_basic();

    //test_sorted();

    //test_remove();

    //test_AVL_BF();

    //test_AVL_BF_1();

    //test_AVL_ROTATE_SINGLE_LEFT();

    //test_AVL_ROTATE_SINGLE_RIGHT();

    //test_AVL_ROTATE_DOUBLE_LEFT();

    //test_AVL_ROTATE_DOUBLE_RIGHT();

    test_ROTATE_INSERT();
   
    return 0;
}
#endif

/*
class CMyString;

class CBase
{
public:
    virtual void SetInfo(void);

protected:
    unsigned int m_nID;
    CMyString m_strName;
};

class CCourse: public CBase
{
    //no more new
};

class CTeacher: public CBase
{
    //no more new
};

class CStudent: public CBase
{
public:
    virtual void SetInfo(void);

public:
    unsigned int m_nSelectiveID;    //ѡ��ID����ѧ��ID�Ϳγ�ID���
};

class CSelective
{
public:
    unsigned int m_nSelectiveID;    //ѡ��ID����ѧ��ID�Ϳγ�ID���
    float m_fscore;                 //�ɼ�
};

class CMyFile
{
protected:
    CMyString m_filename;
};

class CStudInfoFile: public CMyFile
{
public:
    CStudInfoFile(const char *pszfilename = "studinfo.txt");
    //no more new
};

class CCourseInfoFile: public CMyFile
{
public:
    CCourseInfoFile(const char *pszfilename = "courseinfo.txt");
};

class CTeacherInfoFile: public CMyFile
{
public:
    CCourseInfoFile(const char *pszfilename = "teacherinfo.txt");
};

class CSelectiveInfoFile: public CMyFile
{
public:
    CSelectiveInfoFile(const char *pszfilename = "selectiveinfo.txt");
};

template<typename T>
class CTreeNode_NON //��������Ĵ���
{
protected:
    T m_Data;

    //ID���(����ѡ����StudID + CourseID
    CTreeNode *m_pIDParent;
    CTreeNode *m_pIDLeft;
    CTreeNode *m_pIDRight;

    //�������
    CTreeNode *m_pNameParent;
    CTreeNode *m_pNameLeft;
    CTreeNode *m_pNameRight;
};

template<typename T>
class CTreeNode: public CTreeNode_NON
{
protected:
    CTreeNode<T> *m_pNext; //���ͬ������������
};

template<typename T>
class CMyBiTree_NON     //���������tree
{
private:    //���ܱ��̳�
    CTreeNode_NON<T> *m_pRoot;
};

template<typename T>
class CMyBiTree: public CMyBiTree_NON
{
private:
    CTreeNode<T> *m_pRoot;
};

class CStudManage
{
public:

    
private:
    //�ļ����
    CStudInfoFile *m_pStudInfoFile;
    CCourseInfoFile *m_pCourseInfoFile;
    CSelectiveInfoFile *m_pSelectiveInfoFile;
    CTeacherInfoFile *pTeachInfoFile;

    //���������
    //������������϶�Ϊһ
    CMyBiTree_NON<CStudent> m_studIDTree;   //��������Ķ�����
    CMyBiTree<CStudent> m_studNameTree;     //��������Ķ�����

    CMyBiTree_NON<CCourse> m_courseIDTree;
    CMyBiTree<CCourse> m_courseNameTree;

    CMyBiTree_NON<CTeacher> m_teacherIDTree;
    CMyBiTree<CTeacher> m_teacherNameTree;

    CMyBiTree_NON<CSelective> m_seStudCourseTree;
    CMyBiTree_NON<CSelective> m_seCourseStudTree;
};
*/