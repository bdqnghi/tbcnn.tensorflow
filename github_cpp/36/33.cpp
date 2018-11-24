#include "B-tree.h"
#include <malloc.h>
#include <stdio.h>

struct ParentWithChild{   //структура связи родителя и сына
    Node *children;       //узел-сын
    Node *parent;         //узел-родитель
    int position;         //позиция сына в родителе
};

void swap                     ( int *, int * );                                                        //меняем местами два числа
Node* initNode                ( int levelTree );                                                       //инициализация узла дерева
void insertKeyIntoNode        ( Node *, int levelTree, int newKey, string  *newStr );                                   //вставка ключа в узел дерева
void splitNode                ( Node *, int levelTree, int position );                                 //раделение узла на два узла
bool mergeNodes               ( Node *, int levelTree, int positionFirst, int positionSecond );        //соединение узлов
void destroyNode              ( Node *, int levelTree );                                                              //удаление узлов
bool deleteKeyFromLeaf        ( Node *, int levelTree, int positionKey );                              //удаление ключа из узла-листа
ParentWithChild findKeyInTree ( Tree *, int findKey );                                                 //поиск ключа в дереве
ParentWithChild findKeyInNode ( Node *, Node *, int findKey, int positionNode );                       //поиск ключа в узле
int positionKeyInNode         ( Node *, int findKey);                                                  //поиск индекса ключа в узле
ParentWithChild findLeft      ( Node * );                                                              //рекурсивный спуск влево
ParentWithChild findRight     ( Node * );                                                              //рекурсивный спуск вправо
void replaceKeyToLeft         ( Node *, Node *, Node *, int position);                                 //перемещения ключа с права налево
void replaceKeyToRight        ( Node *, Node *, Node *, int position);                                 //перемещения ключа с лева направо
bool deleteKeyFromNode        ( Node *, int levelTree, int deleteKey, int deletePosition );            //удаление ключа из узла

Tree* initTree ( int levelTree )
{
    /*
     * В этой функции мы инициализируем дерево
     * на основе основного свойства B-дерева
     * levelTree - основная характеристика B-дерева
    */

    Tree *temp  = ( Tree * )malloc( sizeof( Tree ) );

    temp->level = levelTree;
    temp->root  = initNode( levelTree );

    return temp;
}

Node* initNode ( int levelTree )
{
    /*
     * Инициализация узла дерева
     * происходит посредством выделения динамической памяти
     * Первоначально узел:
     * 1. Лист ( temp->leaf = true )
     * 2. Пустой ( temp->counter = 0 )
     *
     * levelTree - основная характеристика B-дерева
     */

    Node* temp    = ( Node * )malloc( sizeof( Node ) );

    temp->leaf    = true;
    temp->counter = 0;
    temp->key     = ( int * )malloc( ( 2 * levelTree - 1 ) * sizeof( int ) );
    temp->child   = ( Node ** )malloc( 2 * levelTree * sizeof( Node * ) );
    temp->str     = strMasCreate( 2 *  levelTree - 1 );

    return temp;
}

void insertKeyIntoTree ( Tree *currentTree, int newKey, string *newStr )
{
    /*
     * Добавление ключа в дерево:
     * 1. Если корень переполнен, разбиваем его на два узла,
     *    вставляем в новый корень ключ
     * 2. Иначе просто вставяем ключ в узел
     *
     * currentTree - указатель на дерево, в которое происходит
     *               добавление нового ключа
     * newKey      - новый ключ
     */

    Node* tempRoot = currentTree->root;

    if ( tempRoot->counter == 2 * currentTree->level - 1 ){

        Node *newRoot = initNode( currentTree->level );

        newRoot->leaf     = false;
        currentTree->root = newRoot;
        newRoot->child[0] = tempRoot;

        splitNode( newRoot, currentTree->level, 0 );

        insertKeyIntoNode( newRoot, currentTree->level, newKey, newStr );
    }
    else{

        insertKeyIntoNode( tempRoot, currentTree->level, newKey, newStr );
    }
}

void insertKeyIntoNode ( Node *currentNode, int levelTree, int newKey, string *newStr )
{
    /*
     * Добавление ключа в узел
     * 1. Если узел - лист, то добавляем новый ключ на нужную позицию
     * 2. Иначе, ищем сына, в которого можно вставить элемент, еесли он переполнится
     *    то предварительно необходимо разделить узел на 2
     *
     * currentNode - указатель на текущий узел, который рассматривается в качестве
     *               хранения нового ключа
     * levelTree   - основная характеристика B-дерева
     * newKey      - новый ключ
     */

    int pos = currentNode->counter - 1;

    if ( currentNode->leaf ){

        while ( ( pos >= 0 ) && ( newKey < currentNode->key[ pos ] ) ){

            currentNode->key[ pos + 1 ] = currentNode->key[ pos ];
            strCopy( currentNode->str[ pos ], currentNode->str[ pos + 1 ] );
            pos -= 1;
        }

        currentNode->key[ pos + 1 ] = newKey;
        strCopy( newStr, currentNode->str[ pos + 1 ] );

        currentNode->counter += 1;
    }
    else{

        while ( ( pos >= 0 ) && ( newKey < currentNode->key[ pos ] ) ){

            pos -= 1;
        }

        pos += 1;

        if ( currentNode->child[ pos ]->counter == 2 * levelTree - 1 ){

            if ( currentNode->child[ pos ]->leaf )
                splitNode( currentNode, levelTree, pos );
            else
                splitNode( currentNode, levelTree, ( 2 * levelTree - 1 ) / 2  );

            //printf("%d", currentNode->key[pos] );
            if ( newKey > currentNode->key[ pos ] ) {

                pos += 1;
            }
        }

        insertKeyIntoNode( currentNode->child[ pos ], levelTree, newKey, newStr );
        if ( currentNode->child[ pos ]->counter > 2 * levelTree - 1 )
            splitNode( currentNode, levelTree, pos );

    }
}

void splitNode ( Node *currentNode, int levelTree, int position )
{
    /*
     * Разделение узла на два узла, происходит только
     * если currentNode->counter == 2 * levelTree - 1
     * Узел разбивается на две составляющие
     * по levelTree - 1 элементов и одним элементом
     * как элемент - родитель
     *
     * currentNode - указатель на родителя, который содержит ребенка
     *               с количеством элементов levelTree - 1
     * levelTree   - основная характеристика B-дерева
     * position    - позиция ребёнка в родителе
     */

    Node *firstPart;
    Node *secondPart;

    firstPart  = currentNode->child[ position ];

    secondPart          = initNode( levelTree );
    secondPart->leaf    = firstPart->leaf;
    secondPart->counter = levelTree - 1;

    for ( int j = 0; j < levelTree - 1; j++ ){

        secondPart->key[ j ] = firstPart->key[ j + levelTree ];
        strCopy( firstPart->str[ j + levelTree ], secondPart->str[ j ] );
    }

    if ( !secondPart->leaf ){

        for ( int j = 0; j < levelTree; j++ ){

            secondPart->child[ j ] = firstPart->child[ j + levelTree ];
        }
    }

    firstPart->counter = levelTree;
    firstPart->child[ levelTree ] = secondPart;

    for ( int j = currentNode->counter + 1; j >= position + 1; j-- ){

        currentNode->child[ j + 1 ] = currentNode->child[ j ];
    }

    currentNode->child[ position + 1 ] = secondPart;

    for ( int j = currentNode->counter; j >= position; j-- ){

        currentNode->key[ j + 1 ] = currentNode->key[ j ];

    }

    currentNode->key[ position ] = firstPart->key[ levelTree ];
    strDestroy( currentNode->str[ position ] );
    currentNode->str[ position ] = strCreate();

    currentNode->counter += 1;
}

bool mergeNodes ( Node *currentNode, int levelTree, int positionFirst, int positionSecond )
{
    /*
     * Соединение двух узлов в один
     * Из предка берем текущий ключ, относительно
     * которого выбираются узлы, и опускается в левого предка.
     * В левого предка также сливается правый предок, который
     * впоследствии удаляется.
     * Далее возможны 2 варианта:
     *   1. Если родитель состоял из одного элемента - заменить
     *      его левым ребенком
     *   2. Если родитель состоит из множества элементов - удаляем
     *      искомый элемент
     *
     * currentNode    - рассматриваемый предок, дети которого сольются
     * levelTree      - основная характеристика B-дерева
     * positionFirst  - позиция левого ребенка в currentNode
     * positionSecond - позиция правого ребенка в currentNode
     */

    if ( positionFirst < 0 || positionFirst > currentNode->counter ) {

        return false;
    }

    if ( positionSecond < 0 || positionSecond > currentNode->counter ) {

        return false;
    }

    if ( positionFirst > positionSecond ) {

        swap( &positionFirst, &positionSecond );
    }

    Node *firstNode  = currentNode->child[ positionFirst ];
    Node *secondNode = currentNode->child[ positionSecond ];



    if ( ( firstNode->counter + secondNode->counter + 1 ) > ( 2 * levelTree - 1 ) ){

        return false;
    }

    //firstNode->key[ firstNode->counter ] = currentNode->key[ positionFirst ]; //спускаем предка
    //firstNode->counter += 1;

    for ( int i = 0; i < secondNode->counter; i++ ){

        firstNode->key[ i + firstNode->counter ] = secondNode->key[ i ];
        strCopy( secondNode->str[ i ], firstNode->str[ i + firstNode->counter ] );
    }
    for ( int i = 0; i <= secondNode->counter; i++ ){

        firstNode->child[ i + firstNode->counter ] = secondNode->child[ i ];
    }

    firstNode->counter += secondNode->counter;

    destroyNode( secondNode, levelTree );


    if ( currentNode->counter != 1 ){

        for ( int i = positionFirst; i < currentNode->counter - 1; i++ ) {

            currentNode->key[ i ] = currentNode->key[ i + 1 ];
        }

        for ( int i = positionFirst + 1; i < currentNode->counter; i++ ) {

            currentNode->child[ i ] = currentNode->child[ i + 1 ];
        }

        currentNode->counter -= 1;
    }
    else{

        currentNode->counter = firstNode->counter;
        currentNode->leaf    = firstNode->leaf;

        for ( int i = 0; i < currentNode->counter; i++ ) {

            currentNode->key[ i ] = firstNode->key[ i ];
            strCopy( firstNode->str[ i ], currentNode->str[ i ] );
        }

        for ( int i = 0; i <= currentNode->counter; i++ ) {

            currentNode->child[ i ] = firstNode->child[ i ];
        }

        destroyNode( firstNode, levelTree );
    }

    return true;
}

ParentWithChild findKeyInTree ( Tree *currentTree, int findKey )
{
    /*
     * Поиск ключа в дереве
     * Функция - связка между деревом и его узлами
     *
     * currentTree - рассматриваемое дерево
     * findKey     - искомый ключ
     */

    return findKeyInNode ( currentTree->root, currentTree->root, findKey, 0 );
}

ParentWithChild findKeyInNode ( Node *childNode, Node *parentNode, int findKey, int positionNode )
{
    /*
     * Поиск ключа в узле
     * Методом рекурсивного спуска ищем нужный нам ключ
     * В случае отсутствия ключа в дереве возвращается нулевая структура
     *
     * childNode    - ребенок, в котором ищется findKey
     * parentNode   - родитель childNode
     * findKey      - искомый ключ
     * positionNode - позиция ребенка в родителе
     */

    //printf("231231\n");
    int positionKey = positionKeyInNode( childNode, findKey );

    if ( positionKey == -1 && childNode->leaf ){

        ParentWithChild temp;

        temp.children = NULL;
        temp.parent   = NULL;
        temp.position = -1;

        return temp;
    }

    if ( positionKey != -1 ){

        ParentWithChild temp;

        temp.children = childNode;
        temp.parent   = parentNode;
        temp.position = positionNode;

        return temp;
    }
    for (int i = 1; i < childNode->counter; i++) {

        if (childNode->key[i - 1] > findKey) {

            return findKeyInNode(childNode->child[i - 1], childNode, findKey, i - 1);
        }
    }

    if ( childNode == parentNode ) {
        if (childNode->key[childNode->counter - 1] > findKey) {

            return findKeyInNode(childNode->child[childNode->counter - 1], childNode, findKey, childNode->counter - 1);
        }

    }

    return findKeyInNode( childNode->child[ childNode->counter ], childNode, findKey, childNode->counter );
}

int positionKeyInNode ( Node *currentNode, int findKey )
{
    /*
     * Поиск позиции ключа в узле
     * В случае удачи возвращает индекс ключа в узле
     * В случае не удачи возвращается -1
     */

    if ( !currentNode->leaf )
        return -1;

    for ( int i = 0; i < currentNode->counter; i++ ) {

        if ( currentNode->key[ i ] == findKey ) {

            return i;
        }
    }

    return -1;
}

bool deleteKeyFromTree ( Tree *currentTree, int deleteKey )
{
    /*
     * Удаление ключа в дереве.
     * Сначала проверяем, не пусто ли дерево.
     * Ищем ключ в дереве.
     * Если ключ не наден в дереве, выводим на экран сообщение об отсутствии.
     * Если найденный ключ находится в корне и корень - лист, то просто
     * удаляем ключ в корне.
     * Если найденный ключ находится в листе, то возможно несколько вариантов:
     *     1. В листе больше, чем t - 1 элементов, то просто удаляем ключ в
     *        листе
     *     2. Если в листе ровно t - 1 элементов и он находится с правого края, то:
     *           а) Если в левом соседе больше ( t - 1 ) элементов, то
     *              переносим крайний ключ из левого соседа в лист,
     *              и удаляем ключ в данном листе
     *           б) Если в левом соседе ровно ( t - 1 ) элементов, то
     *              сливаем левого соседа и рассматриваемый лист
     *     3. Если в листе ровно t - 1 элементов:
     *           а) Если в правом соседе больше ( t - 1 ) элементов, то
     *              переносим крайний ключ из правого соседа в лист,
     *              и удаляем ключ в данном листе
     *           б) Если в правом соседе ровно ( t - 1 ) элементов, то
     *              сливаем правого соседа и рассматриваемый лист
     * Если найденный ключ находится в узле, то переходим в функцию удаления ключа
     * из узла
     */

    if ( currentTree == NULL || currentTree->root->counter == 0 ){

        printf("%s\n", "Tree is empty.");

        return 0;
    }

    ParentWithChild temp = findKeyInTree( currentTree, deleteKey );

    if ( temp.position == -1 ){

        printf( "%s\n", "Key don't find in Tree" );

        return 0;
    }

    if ( temp.children == currentTree->root && temp.children->leaf ){

        int pos = positionKeyInNode( temp.children, deleteKey );

        for ( int i = pos; i < temp.children->counter - 1; i++ ){
            temp.children->key[ i ] = temp.children->key[ i + 1 ];
        }


        for ( int i = pos; i <= temp.children->counter - 1; i++ ){
            temp.children->child[ i ] = temp.children->child[ i + 1 ];
        }

        temp.children->counter -= 1;

        return 1;
    }

    if ( temp.children->leaf ){

        if ( temp.children->counter > currentTree->level - 1 ) {

            int pos = positionKeyInNode( temp.children, deleteKey );

            return deleteKeyFromLeaf( temp.children, currentTree->level, pos );
        }
        else {

            if ( temp.position == temp.parent->counter ) {

                if ( temp.parent->child[ temp.position - 1 ]->counter > currentTree->level - 1 ){

                    replaceKeyToRight( temp.parent, temp.parent->child[ temp.position - 1 ], temp.children, temp.position - 1 );

                    int pos = positionKeyInNode( temp.parent->child[ temp.position ], deleteKey );

                    return deleteKeyFromLeaf( temp.parent->child[ temp.position ], currentTree->level, pos );
                }
                else{

                    mergeNodes( temp.parent, currentTree->level, temp.position, temp.position - 1 );

                    if ( temp.parent->leaf ){

                        int pos = positionKeyInNode( temp.parent, deleteKey );

                        return deleteKeyFromLeaf( temp.parent, currentTree->level, pos );
                    }
                    else {

                        int pos = positionKeyInNode(temp.parent->child[temp.position - 1], deleteKey);

                        return deleteKeyFromLeaf(temp.parent->child[temp.position - 1], currentTree->level, pos);
                    }
                }

            }
            else {

                if ( temp.parent->child[ temp.position + 1 ]->counter > currentTree->level - 1 ) {

                    replaceKeyToLeft( temp.parent, temp.children, temp.parent->child[ temp.position + 1 ], temp.position);

                    int pos = positionKeyInNode(temp.children, deleteKey);

                    return deleteKeyFromLeaf(temp.children, currentTree->level, pos);
                }
                else {

                    mergeNodes(temp.parent, currentTree->level, temp.position, temp.position + 1);

                    if ( temp.parent->leaf ){

                        int pos = positionKeyInNode( temp.parent, deleteKey );

                        return deleteKeyFromLeaf( temp.parent, currentTree->level, pos );
                    }
                    else {

                        int pos = positionKeyInNode(temp.children, deleteKey);

                        return deleteKeyFromLeaf(temp.children, currentTree->level, pos);
                    }
                }
            }
        }
    }
    else {

        int pos = positionKeyInNode(temp.children, deleteKey);

        return deleteKeyFromNode( temp.children, currentTree->level, deleteKey , pos );
    }
}

void swap (int *x, int *y)
{
    /*
     * Функиция, меняющая местами два числа
     */

    int t = *x;
    *x = *y;
    *y = t;
}

ParentWithChild findLeft ( Node *childNode)
{
    /*
     * Функция рекурсивного спуска влево
     * Необходима для поиска наименьшего от заданного
     * в родителе числа в правом ребенке
     *
     * childNode - рассматриваемый в текущее время узел
     */

    if ( childNode->child[ 0 ]->leaf ){

        ParentWithChild temp;

        temp.parent   = childNode;
        temp.children = childNode->child[ 0 ];
        temp.position = 0;

        return temp;
    }

    return findLeft( childNode->child[ 0 ] );
}

ParentWithChild findRight ( Node *childNode)
{
    /*
    * Функция рекурсивного спуска вправо
    * Необходима для поиска наименьшего от заданного
    * в родителе числа в левом ребенке
    *
    * childNode - рассматриваемый в текущее время узел
    */

    if ( childNode->child[ childNode->counter ]->leaf ){

        ParentWithChild temp;

        temp.parent = childNode;
        temp.children = childNode->child[ childNode->counter ];
        temp.position = childNode->counter;

        return temp;
    }

    return findRight( childNode->child[ childNode->counter ] );
}

bool deleteKeyFromNode ( Node *currentNode, int levelTree, int deleteKey, int deletePosition ){
    /*
     * Удаление ключа из узла
     * Если текущий узел - лист, переходим в функцию
     * удаления ключа из листа.
     * Затем ищем пару "родитель-ребенок", у которой
     * ребенок лист, и в Left хранится самое ближайшее
     * слева к удаляемому ключу число, а в Right хранится самое
     * ближайщее справа к удаляемому ключу число
     * Затем рассматриваем случаи:
     *    1. Если Left.children содержит больше ( t - 1 ) элемента,
     *       то меняем ключи из текущего узла и Left.children, а затем
     *       переходим в Left.children
     *    2. Иначе если Right.children содержит больше ( t - 1 ) элемента,
     *       то меняем ключи из текущего узла и Right.children, а затем
     *       переходим в Right.children
     *    3. Иначе если правый сосед Right.children содержит больше ( t - 1 ) элемента,
     *       то перекидываем ключ из правого ключи в Right.children и переходм в
     *       последнего
     *    4. Иначе сливаем Right.children и его правого соседа и переходим в
     *       полученный узел
     *
     * currentNode    - узел, в котором производится работа
     * deleteNode     - узел, в которм находится удаляемый объект
     * levelTree      - характеристика дерева
     * deleteKey      - ключ, который мы удаляем
     * deletePosition - позиция deleteKey в deleteNode
     * swapPosition   - индекс на ключ в currentNode, который можно будет поменять
     */

    if ( currentNode->leaf ){

        return deleteKeyFromLeaf( currentNode, levelTree, deletePosition );
    }

    ParentWithChild Left;
    if ( currentNode->child[ deletePosition + 1 ]->leaf){

        Left.parent   = currentNode;
        Left.children = currentNode->child[ deletePosition + 1 ];
        Left.position = deletePosition + 1;
    }
    else{

        findLeft( currentNode->child[ deletePosition + 1 ] );
    }

    ParentWithChild Right;
    if ( currentNode->child[ deletePosition ]->leaf ){

        Right.parent   = currentNode;
        Right.children = currentNode->child[ deletePosition ];
        Right.position = deletePosition;
    }
    else{

        findRight( currentNode->child[ deletePosition ] );
    }

    if ( Left.children->counter > levelTree - 1 ){

        swap( &currentNode->key[ deletePosition ], &Left.children->key[ 0 ] );

        return deleteKeyFromNode( Left.children, levelTree, deleteKey, 0 );
    }
    else{
        if ( Right.children->counter > levelTree - 1 ){

            swap( &currentNode->key[ deletePosition ], &Right.children->key[ Right.children->counter - 1 ] );

            return deleteKeyFromNode( Right.children, levelTree, deleteKey, Right.children->counter - 1 );
        }
        else{
            if ( Right.parent->child[ Right.position + 1 ]->counter > levelTree - 1 ){

                swap( &currentNode->key[ deletePosition ], &Right.parent->key[ Right.position ] );
                replaceKeyToLeft( Right.parent, Right.children, Right.parent->child[ Right.position + 1 ], Right.position );

                int temp = positionKeyInNode( Right.children, deleteKey );

                return deleteKeyFromNode( Right.children, levelTree, deleteKey, temp );
            }
            else{

                swap( &currentNode->key[ deletePosition ], &Right.parent->key[ Right.position ] );

                mergeNodes( Right.parent, levelTree, Right.position, Right.position + 1 );

                if ( Right.parent->leaf ) {

                    int temp = positionKeyInNode( Right.parent, deleteKey );

                    return deleteKeyFromNode( Right.parent, levelTree, deleteKey, temp );
                }
                else{

                    int temp = positionKeyInNode( Right.children, deleteKey );

                    return deleteKeyFromNode( Right.children, levelTree, deleteKey, temp );
                }
            }
        }
    }
}

void replaceKeyToLeft( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    /*
     * Функция перебрасывания ключа с правого ребенка в левого ребенка
     *
     * parentNode     - родителей двух детей
     * leftChildNode  - левый ребенок
     * rightChildNode - правый ребенок
     * position       - позиция ключа, относительно которого рассматриваются
     *                  дети в предке
     */

    leftChildNode->counter += 1;

    leftChildNode->key[ leftChildNode->counter - 1 ] = rightChildNode->key[ 0 ];
    strCopy( rightChildNode->str[0], leftChildNode->str[ leftChildNode->counter - 1 ] );
    leftChildNode->child[ leftChildNode->counter - 1 ]   =  rightChildNode->child[ 0 ];
    leftChildNode->child[ leftChildNode->counter ] = rightChildNode;

    parentNode->key[ position ] = rightChildNode->key[ 1 ];

    for ( int i = 0; i <= rightChildNode->counter; i++ ){

        rightChildNode->child[ i ] = rightChildNode->child[ i + 1 ];
    }

    for ( int i = 0; i < rightChildNode->counter; i++ ){

        rightChildNode->key[ i ] = rightChildNode->key[ i + 1 ];
        strCopy( rightChildNode->str[ i + 1 ], rightChildNode->str[ i ] );
    }

    rightChildNode->counter -= 1;
}

void replaceKeyToRight( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    /*
     * Функция перебрасывания ключа с левого ребенка в правого ребенка
     *
     * parentNode     - родителей двух детей
     * leftChildNode  - левый ребенок
     * rightChildNode - правый ребенок
     * position       - позиция ключа, относительно которого рассматриваются
     *                  дети в предке
     */

    for ( int i = rightChildNode->counter; i > 0; i-- ){

        rightChildNode->key[ i ] = rightChildNode->key[i - 1];
    }

    for ( int i = rightChildNode->counter + 1; i > 0; i-- ){

        rightChildNode->child[ i ] = rightChildNode->child[i - 1];
    }

    rightChildNode->counter += 1;

    rightChildNode->key[ 0 ]   = leftChildNode->key[ leftChildNode->counter - 1 ];
    rightChildNode->child[ 0 ] = leftChildNode->child[ leftChildNode->counter - 1 ];
    rightChildNode->str[ 0 ]   = rightChildNode->str[ leftChildNode->counter - 1 ];

    parentNode->key[ position ] = rightChildNode->key[ 0 ];

    leftChildNode->counter -= 1;
    leftChildNode->child[ leftChildNode->counter ] = rightChildNode;
}

bool deleteKeyFromLeaf ( Node *nodeIsLeaf, int levelTree, int positionKey )
{
    /*
     * Функция удаления ключа из листа
     *
     * nodeIsLeaf  - рассматриваемый лист
     * levelTree   - основная характеристика B-дерева
     * positionKey - позиция ключа в листе
     */

    if ( nodeIsLeaf->counter == levelTree - 1 ) {

        return false;
    }

    for ( int i = positionKey; i < nodeIsLeaf->counter - 1; i++){

        nodeIsLeaf->key[ i ] = nodeIsLeaf->key[ i + 1 ];
        strCopy( nodeIsLeaf->str[ i + 1 ], nodeIsLeaf->str[ i ] );
    }

    for ( int i = positionKey; i < nodeIsLeaf->counter; i++){

        nodeIsLeaf->child[ i ] = nodeIsLeaf->child[ i + 1 ];
    }

    nodeIsLeaf->counter -= 1;

    return true;
}

void wr ( Node *temp, Tree *tr )
{
    printf("%s %d\n", "Start Node:", temp->counter);
    for ( int i = 0; i < temp->counter; i++ ){
        printf("%d ", temp->key[i]);
        strPrint( temp->str[i] );
    }
    printf("\n");
    if ( temp == tr->root ){
        for ( int i = 0; i <= temp->counter; i++ ){
            if ( !temp->leaf )
                wr ( temp->child[i], tr );
        }
        printf("%s\n\n", "End Node.");
    }else {
        if (temp->leaf) {
            for (int i = 0; i < temp->counter; i++) {
                if (!temp->leaf)
                    wr(temp->child[i], tr);
            }
            printf("%s\n\n", "End Leaf.");
        } else {
            for (int i = 0; i < temp->counter; i++) {
                if (!temp->leaf)
                    wr(temp->child[i], tr);
            }
            printf("%s\n\n", "End Node.");
        }
    }
}

void destroyNode ( Node *currentNode, int levelTree )
{
    if ( currentNode != NULL ) {
      //  printf("%s\n", "kek1");
        free(currentNode->child);
        free(currentNode->key);
        //strMasDestroy( currentNode->str, levelTree );
        free(currentNode);
    }
    printf("%s\n", "end");
}

void destroyTree ( Node *deleteNode, int levelTree ) {
    /*
     * Рекурсивное удаление дерева
     */
    if (deleteNode->leaf) {

        destroyNode(deleteNode, levelTree );
    }
    else {

       // printf("%d %d\n", deleteNode->counter, deleteNode->key[1]);


        for (int i = deleteNode->counter; i >= 0; i-- ) {
            printf("%d %d\n", deleteNode->counter, i);
            destroyTree(deleteNode->child[i], levelTree );
        }

        free(deleteNode);
    }


    //printf("%s\n", "keks");
}

void write( Tree *temp )
{
    wr( temp->root, temp );
}