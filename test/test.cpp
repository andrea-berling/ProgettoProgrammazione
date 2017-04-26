#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "/home/andrea/C_C++_Projects/DataStructures/List/include/List.h"

#define COLS 100
#define ROWS 37

enum tile_t { VOID, PAVEMENT, WALL};

enum direction_t { UP, DOWN, LEFT, RIGHT};

enum orientation_t { VERTICAL, HORIZONTAL, NONE};

int randBetween(int first, int second)
{
    if (first < second)
        return first + rand() % (second - first + 1);
    else
        return second + rand() % (first - second + 1);
}

using namespace std;

struct point
{
    int x, y;
};

class Area
{
    protected:

        point position;
        int width, height;

    public:

        Area()
        {
            position = {0,0};
            width = 0;
            height = 0;
        }

        Area(point position, int width, int height)
        {
            this->position = position;
            this->width = width;
            this->height = height;
        }

        void setPosition(point position)
        {
            this->position = position;
        }

        void setWidth(int width)
        {
            this->width = width;
        }

        void setHeight(int height)
        {
            this->height = height;
        }

        point getPosition()
        {
            return position;
        }

        int getWidth()
        {
            return width;
        }

        int getHeight()
        {
            return height;
        }
};

bool operator == (point p1, point p2)
{
    return ((p1.x == p2.x) && (p1.y == p2.y));
}

struct tiles
{
    tile_t tile;
};

void merge(int *A,int first, int half, int last)
{
    int i,j,k,h;
    int *B = new int [last - first];
    i = first;
    j = half + 1;
    k = first;
    while ((i <= half) && (j < last))
    {
        if (A[i] <= A[j])
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }

        k++;
    }

    j = last;

    for (h = half; h > i; h--)
    {
        A[j] = A[h];
        j--;
    }

    for (j = first; j < k; j++)
    {
        A[j] = B[j];
    }
}

void mergeSort(int *A, int first, int last)
{
    if (first < last)
    {
        int half = (first + last) / 2;
        mergeSort(A, first, half);
        mergeSort(A, half + 1, last);
        merge(A, first,half,last);
    }
}

int distance(point p1, point p2)
{
    return sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
}

class Room : public Area
{
    public:

        Room():Area()
        {
        }

        Room(point position, int width, int height) : Area(position,width,height) 
        {
        }

        void place(tiles** A)
        {
            /*for(int i = position.x; i <= position.x + width; i++)
            {
                if (A[position.y][i].tile != PAVEMENT)
                    A[position.y][i].tile = WALL;
                if (A[position.y + height][i].tile != PAVEMENT)
                    A[position.y + height][i].tile = WALL;
            }

            for(int i = position.y; i <= position.y + height; i++)
            {
                if(A[i][position.x].tile != PAVEMENT)
                    A[i][position.x].tile = WALL;
                if(A[i][position.x + width].tile != PAVEMENT)
                    A[i][position.x + width].tile = WALL;
            }*/

            for (int i = position.y; i <= position.y + height; i++)
                for (int j = position.x; j <= position.x + width; j++)
                {
                    A[i][j].tile = PAVEMENT;
                }
        }
};

bool operator != (Room r1, Room r2)
{
    return (!(r1.getPosition() == r2.getPosition()) || r1.getWidth() != r2.getWidth() || r1.getHeight() != r2.getHeight());
}

class Hall: public Area
{
    private:
        orientation_t orientation;
    public:

        Hall():Area()
        {
            orientation = NONE;
        }
        
        Hall(point position, int width, int height, orientation_t orientation):Area(position, width, height)
        {
            this->orientation = orientation;
        }

        void place(tiles** A)
        {
            if (orientation == HORIZONTAL)
            {
             /*   if(A[position.y + 1][position.x].tile != PAVEMENT)
                {
                    A[position.y + 1][position.x].tile = WALL;
                    A[position.y][position.x].tile = WALL;
                    A[position.y + 2][position.x].tile = WALL;
                }

                if(A[position.y + 1][position.x + width].tile != PAVEMENT)
                {
                    A[position.y + 1][position.x + width].tile = WALL;
                    A[position.y][position.x + width].tile = WALL;
                    A[position.y + 2][position.x + width].tile = WALL;
                }*/

                for(int i = position.x; i <= position.x + width; i++)
                {
                    //if (A[position.y + 1][i].tile != PAVEMENT)
                    //{
                        //A[position.y][i].tile = WALL;
                        A[position.y + 1][i].tile = PAVEMENT;
                        //A[position.y + 2][i].tile = WALL;
                    //}
                }

            }
            else if (orientation == VERTICAL)
            {
                /*if(A[position.y][position.x + 1].tile != PAVEMENT)
                {
                    A[position.y][position.x].tile = WALL;
                    A[position.y][position.x + 1].tile = WALL;
                    A[position.y][position.x + 2].tile = WALL;
                }

                if(A[position.y + height][position.x + 1].tile != PAVEMENT)
                {
                    A[position.y + height][position.x].tile = WALL;
                    A[position.y + height][position.x + 1].tile = WALL;
                    A[position.y + height][position.x + 2].tile = WALL;
                }*/

                for(int i = position.y; i <= position.y + height; i++)
                {
                    //if (A[i][position.x + 1].tile != PAVEMENT)
                    //{
                        //A[i][position.x].tile = WALL;
                        A[i][position.x + 1].tile = PAVEMENT;
                        //A[i][position.x + 2].tile = WALL;
                    //}
                }

            }
        }

        orientation_t getOrientation()
        {
            return orientation;
        }

        void setOrientation(orientation_t orientation)
        {
            this->orientation = orientation;
        }
};

List<Hall>* createHall(Room r1, Room r2);

#define NULL_ROOM Room({0,0},0,0)

class Leaf
{
    private:

        unsigned const int MIN_LEAF_SIZE = 8;
        Leaf *leftChild,*rightChild;
        Area A;
        Room R;
        List <Hall>* halls;

    public:

        Leaf()
        {
            leftChild = nullptr;
            rightChild = nullptr;
            R = NULL_ROOM;
            halls = new List<Hall>();
        }

        Leaf(Area A)
        {
            this->A = A;
            leftChild = nullptr;
            rightChild = nullptr;
            R = NULL_ROOM;
            halls = new List<Hall>();
        }

        bool split()
        {
            if ((leftChild != nullptr) || (rightChild != nullptr))
                return false;

            bool splitH;

            if ((A.getWidth() > A.getHeight()) && ((static_cast<double>(A.getWidth()) / A.getHeight()) >= 1.25))
                splitH = false;
            else if ((A.getHeight() > A.getWidth()) && ((static_cast<double>(A.getHeight()) / A.getWidth()) >= 1.25))
                splitH = true;

            int max = (splitH ? A.getHeight() : A.getWidth()) - MIN_LEAF_SIZE;

            if (max <= MIN_LEAF_SIZE)
                return false;

            int split = randBetween(MIN_LEAF_SIZE, max);

            if(splitH)
            {
                leftChild = new Leaf({A.getPosition(), A.getWidth(), split});
                rightChild = new Leaf({{A.getPosition().x, A.getPosition().y + split}, A.getWidth(), A.getHeight() - split});
            }
            else
            {
                leftChild = new Leaf({A.getPosition(), split, A.getHeight()});
                rightChild = new Leaf({{A.getPosition().x + split, A.getPosition().y}, A.getWidth() - split, A.getHeight()});
            }

            return true;

        }

        void createRooms()
        {
            if (leftChild != nullptr || rightChild != nullptr)
            {
                if (leftChild != nullptr)
                    leftChild->createRooms();
                if (rightChild != nullptr)
                    rightChild->createRooms();

                if (rightChild != nullptr && leftChild != nullptr)
                {
                    this->setHall(createHall(rightChild->getRoom(), leftChild->getRoom()));
                }
            }
            else
            {
                point position = { randBetween(A.getPosition().x + 1,A.getPosition().x + A.getWidth() - 6),  randBetween(A.getPosition().y + 1, A.getPosition().y + A.getHeight() - 6)};
                int width = randBetween( 5, A.getWidth() - position.x - 1 + A.getPosition().x);
                int height = randBetween( 5, A.getHeight() - position.y - 1 + A.getPosition().y);
                R = Room(position, width, height);
            }
        }

        void placeHalls(tiles** A)
        {
            List<Hall>* i = halls->head();
            
            while(!halls->finished(i))
            {
                halls->read(i).place(A);
                i = halls->next(i);
            }
        }

        void setleftChild(Leaf *left)
        {
            leftChild = left;
        }

        void setrightChild(Leaf *right)
        {
            rightChild = right;
        }

        void setArea(Area A)
        {
            this->A = A; 
        }

        void setRoom(Room R)
        {
            this->R = R;
        }

        Leaf* getleftChild()
        {
            return leftChild;
        }

        Leaf* getrightChild()
        {
            return rightChild;
        }

        Area getArea()
        {
            return A;
        }

        Room getRoom()
        {
            if (R != NULL_ROOM)
                return R;
            else
            {
                Room l,r;

                if (leftChild != nullptr)
                {
                    l = leftChild->getRoom();
                }

                if (rightChild != nullptr)
                {
                    r = rightChild->getRoom();
                }

                if (leftChild == nullptr && rightChild == nullptr)
                {
                    return NULL_ROOM;
                }
                else if (leftChild == nullptr)
                {
                    return r;
                }
                else if (rightChild == nullptr)
                {
                    return l;
                }
                else
                {
                    if(randBetween(0,1))
                        return l;
                    else
                        return r;
                }
            }
        }

        void setHall(List<Hall>* halls)
        {
            this->halls = halls;
        }

        List<Hall>* getHalls()
        {
            return halls;
        }
};

List<Leaf*>* splitMap();

void generateMap(tiles **A);

void printMatrix(tiles **A, int rows, int cols);

int main()
{
    tiles **A;
    A = new tiles* [ROWS];
    for (int i = 0; i < ROWS; i++)
        A[i] = new tiles [COLS];

    generateMap(A);
    printMatrix(A,ROWS,COLS);
}

void generateMap(tiles **A)
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
        {
            A[i][j].tile = WALL;
        }

    srand(time(NULL));
    List<Leaf*> *_rooms = splitMap();
    List<Leaf*> *i = _rooms->head();
    while(!_rooms->finished(i))
    {
        if ((_rooms->read(i)->getleftChild() == nullptr) && (_rooms->read(i)->getrightChild() == nullptr))
        {
            _rooms->read(i)->getRoom().place(A);
        }

        if (!(_rooms->read(i)->getHalls()->empty()))
        {
            _rooms->read(i)->placeHalls(A);
        }
        i = _rooms->next(i);
    }
}

void printMatrix(tiles **A, int rows, int cols)
{
    for( int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (A[i][j].tile == WALL)
                cout << "#";
            else if ((A[i][j].tile == PAVEMENT) || (A[i][j].tile == VOID))
                cout << " ";
        }
        cout << endl;
    }
}

List<Leaf*> *splitMap()
{
    const unsigned int MAX_LEAF_SIZE = 20;
    
    List<Leaf*> *l = new List<Leaf*>();
    List<Leaf*> *i;

    Area map({{0,0}, COLS - 1, ROWS - 1});
    Leaf root(map);

    l->insert(l->next(l->tail()),&root);

    bool did_split = true;

    i = l->head();

    while(did_split)
    {
        did_split = false;

        while (!l->finished(i))        
        {
            if((l->read(i)->getleftChild() == nullptr) && (l->read(i)->getrightChild() == nullptr))
            {
                if (l->read(i)->getArea().getWidth() > MAX_LEAF_SIZE || l->read(i)->getArea().getHeight() > MAX_LEAF_SIZE )
                {
                    if (l->read(i)->split())
                    {
                        l->insert(l->next(l->tail()),l->read(i)->getleftChild());
                        l->insert(l->next(l->tail()),l->read(i)->getrightChild());
                        did_split = true;
                    }

                }
            }
            
            i = l->next(i);
        }
    }
    
    i = l->head();

    while(!l->finished(i))
    {
        l->read(i)->createRooms();
        i = l->next(i);
    }

    return l;
}

List<Hall>* createHall(Room r1, Room r2)
{
    List<Hall>* halls = new List<Hall>();

    point p1 = { randBetween(r1.getPosition().x + 1,r1.getPosition().x + r1.getWidth() - 2) , randBetween(r1.getPosition().y + 1,r1.getPosition().y + r1.getHeight() - 2) };
    point p2 = { randBetween(r2.getPosition().x + 1,r2.getPosition().x + r2.getWidth() - 2) , randBetween(r2.getPosition().y + 1,r2.getPosition().y + r2.getHeight() - 2) };

    int d1 = p2.x - p1.x;
    int d2 = p2.y - p1.y;

    if (d1 < 0)         // p2 is on the left of p1
    {
        if (d2 < 0)     // p2 is higher than p1
        {
            Hall h1 = Hall({p1.x - 1, p2.y - 1}, 2, abs(d2) + 1, VERTICAL);
            Hall h2 = Hall({p2.x, p2.y - 1}, abs(d1) + 1, 2, HORIZONTAL);

            halls->insert(halls->next(halls->tail()), h1);
            halls->insert(halls->next(halls->tail()), h2);
        }
        else if (d2 > 0)    // p2 is lower than p1
        {
            Hall h1 = Hall({p1.x - 1, p1.y}, 2, abs(d2) + 1, VERTICAL);
            Hall h2 = Hall({p2.x, p2.y - 1}, abs(d1) + 1, 2, HORIZONTAL);

            halls->insert(halls->next(halls->tail()), h1);
            halls->insert(halls->next(halls->tail()), h2);
        }
        else    // d2 == 0 -> p1 and p2 are on the same horizontal line
        {
            Hall h = Hall({p2.x, p2.y - 1}, abs(d1), 2, HORIZONTAL);

            halls->insert(halls->next(halls->tail()), h);
        }
    }
    else if (d1 > 0)    // p2 is on the right of p1
    {
        if (d2 < 0)     // p2 is higher than p1
        {
            Hall h1 = Hall({p1.x - 1, p2.y - 1}, 2, abs(d2) + 1, VERTICAL);
            Hall h2 = Hall({p1.x - 1, p2.y - 1}, abs(d1) + 1, 2, HORIZONTAL);

            halls->insert(halls->next(halls->tail()), h1);
            halls->insert(halls->next(halls->tail()), h2);
        }
        else if (d2 > 0)    // p2 is lower than p1
        {
            Hall h1 = Hall({p1.x - 1, p1.y}, 2, abs(d2) + 1, VERTICAL);
            Hall h2 = Hall({p1.x - 1, p2.y - 1}, abs(d1) + 1, 2, HORIZONTAL);

            halls->insert(halls->next(halls->tail()), h1);
            halls->insert(halls->next(halls->tail()), h2);
        }
        else    // d2 == 0 -> p1 and p2 are on the same horizontal line
        {
            Hall h = Hall({p1.x, p1.y - 1}, abs(d1), 2, HORIZONTAL);

            halls->insert(halls->next(halls->tail()), h);
        }
    }
    else // d1 == 0 -> p1 and p2 are on the same vertical line
    {
        if (d2 < 0)     // p2 is higher than p1
        {
            Hall h = Hall({p2.x - 1, p2.y}, 2, abs(d2), VERTICAL);

            halls->insert(halls->next(halls->tail()), h);
        }
        else if (d2 > 0)    // p2 is lower than p1
        {
            Hall h = Hall({p1.x - 1, p1.y}, 2, abs(d2), VERTICAL);

            halls->insert(halls->next(halls->tail()), h);
        }
        // d2 can't be 0, otherwise they would be the same point
    }

    return halls;

}
