#include <memory.h>
#include "commdef.h"
#include "heapSort.h"
#include <stdio.h>
#include "CATCH.h"

void heapSort::printHeapSort()
{
    printf("This is heap sort file!\n");

}

heapSort::heapSort(U32 eleNum)
{
    (void)initHeap(eleNum);
}

heapSort::~heapSort()
{
    (void)destroyHeap();
}
/* ��ʼ���� */
U32 heapSort::initHeap(U16 eleNum)
{
    TRY
    {
        heapData.maxEleNum = eleNum;
        heapData.currentEleNum = 0;

        heapData.pData = new HEAP_DATA_STR[eleNum];
        THROW_IF(0 == heapData.pData);

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}

U32 heapSort::printHeapData()
{
    if (0 == heapData.maxEleNum) return ok;
    unsigned int index = 0;
    printf("maxEleNum[%3d], currentEleNum[%3d].\n", heapData.maxEleNum,heapData.currentEleNum);
    for (index = 0; index < heapData.currentEleNum; index++)
    {

        printf("[%3d] : %10d\n", index, heapData.pData[index].data);
    }

    return ok;
}

U32 heapSort::destroyHeap()
{

    if (null == heapData.pData) return ok;
    HEAP_DATA_STR *pstData = heapData.pData;
    delete [] (pstData);
    heapData.maxEleNum = 0;
    heapData.pData = 0;

    return ok;
}
/*
���룺�������ݵ�����
���ܣ���֤������������������������Ϊ��С�ѣ��ú���ʹ����������Ϊ�������������С������
���أ�ִ�н��
*/
U32 heapSort::keepMinHeap(U32 eleIndex)
{
    TRY
    {
        U32 minIndex = eleIndex;
        return_if(eleIndex >= heapData.currentEleNum, ok);
        if (LEFT_NODE(eleIndex) < heapData.currentEleNum
            && isABiggerThanB(&(heapData.pData[minIndex]), &(heapData.pData[LEFT_NODE(eleIndex)])))
        {
            minIndex = LEFT_NODE(eleIndex);
        }
        
        if (RIGHT_NODE(eleIndex) < heapData.currentEleNum
            && isABiggerThanB(&(heapData.pData[minIndex]), &(heapData.pData[RIGHT_NODE(eleIndex)])))
        {
            minIndex = RIGHT_NODE(eleIndex);
        }

        if (minIndex != eleIndex)
        {
            EXEC(exchangeEle(&(heapData.pData[minIndex]), &(heapData.pData[eleIndex])));

            EXEC(keepMinHeap(minIndex));
        }

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}
/*
���룺�����ݵĸ�����������˳��洢��ͷָ��
���ܣ��洢����Ķ�������
���أ�ִ�н��
*/
U32 heapSort::inputHeapData(U32 eleNum, HEAP_DATA_STR *pData)
{
    TRY
    {
        if (eleNum > heapData.maxEleNum) return 1;
        THROW_IF(0 == memcpy(heapData.pData, pData, eleNum * sizeof(HEAP_DATA_STR)));
        heapData.currentEleNum = eleNum;
        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}

/*
���룺��
���ܣ�������Ķ����ݽ��в�����ʹ֮��Ϊ��С��
���أ�ִ�н��
*/
U32 heapSort::newBuildMinHeapData()
{
    TRY
    {
        THROW_IF(heapData.currentEleNum >= heapData.maxEleNum);

        for (int i = heapData.currentEleNum / 2 - 1; i >= 0; i--)
        {
            EXEC(keepMinHeap(i));
        }

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}

/*
���룺��(�����ݱ�֤��С������)
���ܣ��Զ����ݽ���ԭ�����򣬰���������
���أ�ִ�н��
*/
U32 heapSort::newSortMinHeapData()
{
    int eleNum = heapData.currentEleNum;
    TRY
    {
        while (0 != heapData.currentEleNum)
        {
            heapData.currentEleNum--;
            EXEC(exchangeEle(&heapData.pData[heapData.currentEleNum], &heapData.pData[0]));
            EXEC(keepMinHeap(0));
        }

        heapData.currentEleNum = eleNum;
        return ok;
    }
    CATCH
    {
        heapData.currentEleNum = eleNum;
        return ERR_CODE;
    }
}

/*
���룺��
���ܣ����ض�����СֵԪ��
���أ�ִ�н��
*/
U32 heapSort::getMinHeapEle(HEAP_DATA_STR *pData)
{
    TRY
    {
        THROW_IF(null == pData);
        THROW_IF(heapData.currentEleNum == 0);
        EXEC(0 == memcpy(pData, heapData.pData, sizeof(HEAP_DATA_STR)));

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}

/*
���룺��
���ܣ����ض�����СԪ�أ���ɾ����Ԫ��
���أ�ִ�н��
*/
U32 heapSort::popMinEle(HEAP_DATA_STR *pData)
{
    TRY
    {
        EXEC(getMinHeapEle(pData));

        heapData.currentEleNum--;
        EXEC(0 == memcpy(heapData.pData, &heapData.pData[heapData.currentEleNum], sizeof(HEAP_DATA_STR)));

        EXEC(keepMinHeap(0));

        return ok;
    }
        CATCH
    {
        return ERR_CODE;
    }
}

U32 heapSort::createHeap(U32 EleNum, HEAP_DATA_STR *pData)
{
    TRY
    {
        THROW_IF(heapData.currentEleNum + EleNum > heapData.maxEleNum);
        THROW_IF(0 == pData);

    //    THROW_IF(0 == memcpy(&(heapData.pData[heapData.currentEleNum]), &(pData[0]), EleNum * sizeof(HEAP_DATA_STR)));
    //    heapData.currentEleNum += EleNum;

        for (unsigned int index = 0; index < EleNum; index++)
        {
            EXEC(insertHeapEle(&pData[index]));
        }
        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}

U32 heapSort::buildMinHeap()
{
    TRY
    {
        unsigned int posIndex = 0;
        unsigned int minIndex = 0;
        U32 eleNum = heapData.currentEleNum;
        while (posIndex < eleNum/2)
        {
            minIndex = posIndex;
             if (LEFT_NODE(posIndex) < eleNum && isABiggerThanB(&heapData.pData[minIndex], &heapData.pData[LEFT_NODE(posIndex)]))
             {
                 minIndex = LEFT_NODE(posIndex);
             }

             if (RIGHT_NODE(posIndex) < eleNum && isABiggerThanB(&heapData.pData[minIndex],&heapData.pData[RIGHT_NODE(posIndex)]))
             {
                 minIndex = RIGHT_NODE(posIndex);
             }
            if (minIndex == posIndex) break;

            EXEC(exchangeEle(&heapData.pData[posIndex], &heapData.pData[minIndex]));
            posIndex = minIndex;
        }
        return ok;
        
    }
    CATCH
    {
        return ERR_CODE;
    }
}
/*
���룺Ҫд��ѵ�����
���ܣ������Ԫ�أ���������С������
���أ�ִ�н��
*/
U32 heapSort::insertHeapEle(HEAP_DATA_STR *pData)
{
    TRY
    {
        int index = 0;
        THROW_IF(heapData.maxEleNum == heapData.currentEleNum);

        EXEC(0 == memset(&heapData.pData[heapData.currentEleNum], 0x7F, sizeof(HEAP_DATA_STR)));
        heapData.currentEleNum++;
        EXEC(decreaseValueByIndex(heapData.currentEleNum-1, pData));

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}
/*
���룺����������ֵ
���ܣ���������ֵ��Ӧ��Ԫ�ص�ֵ
���أ�ִ�н��
*/
U32 heapSort::decreaseValueByIndex(U32 index, HEAP_DATA_STR *pData)
{
    TRY
    {
        THROW_IF(heapData.currentEleNum <= index);
        THROW_IF(pData == null);

        THROW_IF(isABiggerThanB(pData, &heapData.pData[index]));
        EXEC(0 == memcpy(&heapData.pData[index], pData, sizeof(HEAP_DATA_STR)));

        while (0 != index)
        {
            if (isABiggerThanB(&heapData.pData[FATHER_NODE(index)], &heapData.pData[index]))
            {
                EXEC(exchangeEle(&heapData.pData[FATHER_NODE(index)], &heapData.pData[index]));
                index = FATHER_NODE(index);
            }
            else
            {
                index = 0;
            }
        }

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}

bool heapSort::isABiggerThanB(HEAP_DATA_STR *pA, HEAP_DATA_STR *pB)
{
    if (0 == pA || 0 == pB) return False;
    if (pA->data > pB->data) return True;
    return False;
}

U32 heapSort::exchangeEle(HEAP_DATA_STR *pA, HEAP_DATA_STR *pB)
{
    TRY
    {
        HEAP_DATA_STR dataTemp = {0};
        THROW_IF(0 == pA || 0 == pB);

        THROW_IF(0 == memcpy(&dataTemp, pA, sizeof(HEAP_DATA_STR)));
        
        THROW_IF(0 == memcpy(pA, pB, sizeof(HEAP_DATA_STR)));

        THROW_IF(0 == memcpy(pB, &dataTemp, sizeof(HEAP_DATA_STR)));

        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }

}

U32 heapSort::popHeapEle(HEAP_DATA_STR *pData)
{
    TRY
    {
        THROW_IF(0 == pData);

        THROW_IF(0 == heapData.currentEleNum);

        THROW_IF(0 == memcpy(pData, heapData.pData, sizeof(HEAP_DATA_STR)));
        (heapData.currentEleNum)--;
        if (0 == heapData.currentEleNum) return ok;
        THROW_IF(0 == memcpy(heapData.pData, &heapData.pData[heapData.currentEleNum], sizeof(HEAP_DATA_STR)));
        EXEC(buildMinHeap());
        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }

}

U32 heapSort::sortHeapData(U32 eleNum, HEAP_DATA_STR *pData)
{
    TRY
    {
        THROW_IF(eleNum != heapData.currentEleNum);
        for (unsigned int index = 0; index < eleNum; index++)
        {
            EXEC(popHeapEle(&pData[index]));
        }
        return ok;
    }
    CATCH
    {
        return ERR_CODE;
    }
}


void testHeapSort()
{
    TRY
    {
        HEAP_DATA_STR temp = { 0 };
        heapSort a(20);
        heapSort b(20);

        HEAP_DATA_STR data[] = { { 2 },{ 10 },{ 3 },{ 4 },{ 1 },{ 5 },{ 1 },{ 12 },{ 30 },{ 50 },{ 22 } };
        HEAP_DATA_STR data1 = { 0 };
        HEAP_DATA_STR dataOut = { 0 };
        EXEC(b.inputHeapData(sizeof(data) / sizeof(data[0]), data));
        EXEC(b.printHeapData());
        //        EXEC(b.keepMinHeap(0));
        EXEC(b.newBuildMinHeapData());
        EXEC(b.printHeapData());

        EXEC(b.getMinHeapEle(&dataOut));
        EXEC(b.printHeapData());
        EXEC(b.insertHeapEle(&data1));
        EXEC(b.printHeapData());
        //        EXEC(b.newSortMinHeapData());
        //        EXEC(b.printHeapData());
        EXEC(b.popMinEle(&data1));
        EXEC(b.printHeapData());
        /*
        EXEC(a.createHeap(7, &(data[0])));
        EXEC(a.printHeapData());
        EXEC(a.sortHeapData(7, data));
        printf("=========================\n");
        for (int index = 0; index <7; index++)
        {
        printf("[%3d] [%10d]\n", index, data[index].data);
        }
        EXEC(a.printHeapData());

        */
        return;
    }
    CATCH
    {
        printf("This is Catch!\n");
        return;
    }
}
