#include <iostream>
#include <cmath> // only std::sqrt

struct CStudent
{
    char m_cStudentName[20];
    int  m_iScore;
};

struct CPoint
{
    double dX;
    double dY;
};

struct CBooks
{
    char m_cAuthor[20];
    int  m_iPagesCount;
    int  m_iYear;
};

struct CRunners
{
    int m_iRunnerNumber;
    int m_iFinishTime_msec;
};

struct CStudentsGroup
{
    CStudent m_cStudents[20];
    int      m_StudentsAmount;
    int      m_GroupId;
};

double GetAverageStudentsScore(CStudentsGroup* pStudentsGroups, const int& iGroupCount)
{
    double dScoreSum = 0.;
    int    iStudentsAmount = 0;

    for (int i = 0; i < iGroupCount; i++)
    {
        for(int j = 0; j < pStudentsGroups[i].m_StudentsAmount; j++)
        {
            iStudentsAmount++;
            dScoreSum += pStudentsGroups[i].m_cStudents[j].m_iScore;
        }
    }

    return dScoreSum/((double) iStudentsAmount);
}

bool InsertData(CStudentsGroup* pStudentsGroups, const int& iGroupCount)
{
    std::cout << "Enter group id and how much students in every group" << std::endl;

    for (int i = 0; i < iGroupCount; i++)
    {
        std::cout << "Enter next group id (id must be > 0)" << std::endl;
        std::cin >> pStudentsGroups[i].m_GroupId;

        if (pStudentsGroups[i].m_GroupId <= 0)
        {
            std::cout << "Group id must be > 0" << std::endl;
            return false;
        }

        std::cout << "How much students at group " << pStudentsGroups[i].m_GroupId << " (1-20)?" << std::endl;
        std::cin >> pStudentsGroups[i].m_StudentsAmount;

        if (pStudentsGroups[i].m_StudentsAmount <= 0 || pStudentsGroups[i].m_StudentsAmount > 20)
        {
            std::cout << "Students amount must be 1-20" << std::endl;
            return false;
        }
        else
        {
            std::cout << "Now enter all students from " << pStudentsGroups[i].m_GroupId
                      << " group (Student: name, score)" << std::endl;
            for (int j = 0; j < pStudentsGroups[i].m_StudentsAmount; j++)
            {
                std::cout << "Now enter next student (name, score)" << std::endl;

                std::cin >> pStudentsGroups[i].m_cStudents[j].m_cStudentName;
                std::cin >> pStudentsGroups[i].m_cStudents[j].m_iScore;
            }
        }
    }

    return true;
}

void ShowWeakStudents(CStudentsGroup* pStudentsGroups, const int& iGroupCount, const double& dAverageScore)
{
    for (int i = 0; i < iGroupCount; i++)
    {
        for (int j = 0; j < pStudentsGroups[i].m_StudentsAmount; j++)
        {
            if (pStudentsGroups[i].m_cStudents[j].m_iScore < dAverageScore)
            {
                std::cout << "Weak student: from group " << pStudentsGroups[i].m_GroupId << ": "
                          << pStudentsGroups[i].m_cStudents[j].m_cStudentName
                          << " with score: " << pStudentsGroups[i].m_cStudents[j].m_iScore << std::endl;
            }
        }
    }
}

void Exercise7()
{
    // Exercise7: Ввести информацию о группах (массив студентов и номер группы)
    // студентов (имя и оценка) и вывести всех студентов в каждой группе,
    // оценка которых меньше среднего арифметического среди всех студентов
    // во всех группах

    int    iGroupCount = 0;
    double dAverageScore = 0.;
    std::cout << "Enter group amount" << std::endl;
    std::cin >> iGroupCount;

    if (iGroupCount <= 0)
    {
        std::cout << "Group amount should be > 0" << std::endl;
        return;
    }

    CStudentsGroup* pStudentsGroups = new CStudentsGroup[iGroupCount];

    bool bWrongInputData = !InsertData(pStudentsGroups, iGroupCount);

    if (bWrongInputData)
    {
        delete[] pStudentsGroups;
        return;
    }

    dAverageScore = GetAverageStudentsScore(pStudentsGroups, iGroupCount);
    std::cout << "Average score is: " << dAverageScore << std::endl;

    ShowWeakStudents(pStudentsGroups, iGroupCount, dAverageScore);

    delete[] pStudentsGroups;
}

void RunnersSwap(CRunners* pRunners, const int& iStartPos, const int& iEndPos)
{
    if (iStartPos != iEndPos)
    {
        int iRunnerNumberCopy = pRunners[iStartPos].m_iRunnerNumber;
        int iRunnerTimeCopy   = pRunners[iStartPos].m_iFinishTime_msec;

        pRunners[iStartPos].m_iRunnerNumber    = pRunners[iEndPos].m_iRunnerNumber;
        pRunners[iStartPos].m_iFinishTime_msec = pRunners[iEndPos].m_iFinishTime_msec;

        pRunners[iEndPos].m_iRunnerNumber    = iRunnerNumberCopy;
        pRunners[iEndPos].m_iFinishTime_msec = iRunnerTimeCopy;
    }
}

void RunnerSort(CRunners* pRunners, const int& iRunnersCount)
{
    int iCurSortPos = 0;
    for (int i = 0; i < iRunnersCount; i++)
    {
        int iCurrentMinIndex = 0;

        for (int j = iCurSortPos; j < iRunnersCount; j++)
        {
            if (j == iCurSortPos)
            {
                iCurrentMinIndex = j;
                continue;
            }

            if (pRunners[iCurrentMinIndex].m_iFinishTime_msec > pRunners[j].m_iFinishTime_msec)
                iCurrentMinIndex = j;
        }

        RunnersSwap(pRunners, iCurSortPos, iCurrentMinIndex);
        iCurSortPos++;
    }
}

void ShowSortedRunners(CRunners* pRunners, int iRunnersCount)
{
    while(iRunnersCount)
    {
        iRunnersCount--;
        std::cout << "Runner number: " << pRunners[iRunnersCount].m_iRunnerNumber << ", time (msec): "
                  << pRunners[iRunnersCount].m_iFinishTime_msec << std::endl;
    }
}

void Exercise6()
{
    // Exercise6: Ввести информацию о результате забега спортсменов
    // (стартовый номер и время, за которое спортсмен прибежал)
    // и вывести все результаты по убыванию времени

    int iRunnersCount = 0;
    std::cout << "Enter count of runners" << std::endl;
    std::cin >> iRunnersCount;

    if (iRunnersCount <= 0)
    {
        std::cout << "Runners count should be > 0" << std::endl;
        return;
    }

    CRunners* pRunners = new CRunners[iRunnersCount];

    std::cout << "Now enter all runners (" << iRunnersCount
              << ") with: start number, finish time (msec)" << std::endl;

    for (int i = 0; i < iRunnersCount; i++)
    {
        std::cout << "Now enter next runner" << std::endl;
        std::cin >> pRunners[i].m_iRunnerNumber;
        std::cin >> pRunners[i].m_iFinishTime_msec;
    }

    RunnerSort(pRunners, iRunnersCount);
    ShowSortedRunners(pRunners, iRunnersCount);

    delete[] pRunners;
}

void FindOldestBook(CBooks* pBooksOnShelf, const int& iHalfCount)
{
    int iOldestBookIndex = 0;

    for (int i = 1; i < iHalfCount; i++)
    {
        if (pBooksOnShelf[i].m_iYear < pBooksOnShelf[iOldestBookIndex].m_iYear)
            iOldestBookIndex = i;
    }

    std::cout << "Oldest book is: " << pBooksOnShelf[iOldestBookIndex].m_cAuthor << ", "
              << pBooksOnShelf[iOldestBookIndex].m_iPagesCount << ", "
              << pBooksOnShelf[iOldestBookIndex].m_iYear << std::endl;
}

void Exercise5()
{
    // Exercise5: Ввести информацию о книгах (автор, количество страниц, год)
    // на книжной полке (заполнить массив) и найти самую старую книгу, стоящей
    // в первой половине книг

    int iBooksCount = 0;
    std::cout << "Enter how much books your have (to find oldest at first part)" << std::endl;
    std::cin >> iBooksCount;

    if (iBooksCount <= 0)
    {
        std::cout << "Books count must be > 0" << std::endl;
        return;
    }

    CBooks* pBooksOnShelf = new CBooks[iBooksCount];
    std::cout << "Now enter all your books (" << iBooksCount << ") with: author, page count, year;"
              << std::endl;

    for (int i = 0; i < iBooksCount; i++)
    {
        std::cout << "Now enter next book" << std::endl;
        std::cin >> pBooksOnShelf[i].m_cAuthor;
        std::cin >> pBooksOnShelf[i].m_iPagesCount;
        std::cin >> pBooksOnShelf[i].m_iYear;
    }
    std::cout << std::endl;

    int iHalfCount;
    if (!(iBooksCount%2))
        iHalfCount = iBooksCount >> 1;
    else
        iHalfCount = (iBooksCount >> 1) + 1;

    FindOldestBook(pBooksOnShelf, iHalfCount);

    delete[] pBooksOnShelf;
}

void FindWeakStudents(CStudent* pStudents, const int& iElementsCount)
{
    int iTotalScoreSum = 0;
    for (int i = 0; i < iElementsCount; i++)
    {
        iTotalScoreSum += pStudents[i].m_iScore;
    }

    double dAverageScore = (double) iTotalScoreSum/iElementsCount;

    for (int i = 0; i < iElementsCount; i++)
    {
        if (pStudents[i].m_iScore < dAverageScore)
            std::cout << "Weak student: " << pStudents[i].m_cStudentName << std::endl;
    }
}

void Exercise4()
{
    // Exercise4: Используя вторую задачу, вывести всех студентов, оценка
    // которых меньше средней

    const int iStudentsCount = 5;
    std::cout << "Enter 5 students, for each: name, score (to find weak students)" << std::endl;

    CStudent* pStudents = new CStudent[iStudentsCount];

    for (int i = 0; i < iStudentsCount; i++)
    {
        std::cout << "Next student: " << std::endl;

        std::cin >> pStudents[i].m_cStudentName;
        std::cin >> pStudents[i].m_iScore;
    }

    std::cout << std::endl;

    FindWeakStudents(pStudents, iStudentsCount);

    delete[] pStudents;
}

double GetPointsDistance(const CPoint& pPoint1, const CPoint& pPoint2)
{
    double dTriangleSideX = pPoint1.dX - pPoint2.dX;
    double dTriangleSideY = pPoint1.dY - pPoint2.dY;

    return std::sqrt(dTriangleSideX*dTriangleSideX + dTriangleSideY*dTriangleSideY);
}

void SearchFarthestPoints(CPoint* pPoint, const int& iTotalPoints)
{
    double dMaximumDistance = 0;
    CPoint FirstPoint;
    CPoint SecondPoint;

    for (int i = 0; i < iTotalPoints; i++)
    {
        for (int j = i + 1; j < iTotalPoints; j++)
        {
            double dDistance = GetPointsDistance(pPoint[i], pPoint[j]);

            if (dDistance > dMaximumDistance)
            {
                dMaximumDistance = dDistance;

                FirstPoint.dX  = pPoint[i].dX;
                FirstPoint.dY  = pPoint[i].dY;
                SecondPoint.dX = pPoint[j].dX;
                SecondPoint.dY = pPoint[j].dY;
            }
        }
    }

    std::cout << "Farthest points: first (" << FirstPoint.dX << ", " << FirstPoint.dY << "), "
              << "second (" << SecondPoint.dX << ", " << SecondPoint.dY << ")" << std::endl;
    std::cout << "Maximum distance is: " << dMaximumDistance << std::endl;
}

void Exercise3()
{
    // Exercise3: В массиве точек найти две такие точки, расстояние между
    // которыми является максимальным (вывести их координаты)

    const int iTotalPoints = 5;
    CPoint* pPoints = new CPoint[iTotalPoints];

    std::cout << "Enter 5 points, for each: x, y (to find farthest points)" << std::endl;
    for (int i = 0; i < iTotalPoints; i++)
    {
        std::cout << "Enter next point" << std::endl;
        std::cin >> pPoints[i].dX;
        std::cin >> pPoints[i].dY;
    }

    std::cout << std::endl;

    SearchFarthestPoints(pPoints, iTotalPoints);

    delete[] pPoints;
}

void CalculateArithmeticMean(CStudent* pStudents, const int& iElementsCount)
{
    int iTotalScoreSum = 0;
    for (int i = 0; i < iElementsCount; i++)
    {
        iTotalScoreSum += pStudents[i].m_iScore;
    }

    double dAverageScore = (double) iTotalScoreSum/iElementsCount;

    std::cout << "Arithmetic mean of student's scores is: " << dAverageScore << std::endl;
}

void Exercise2()
{
    // Exercise2: Используя данные первой задачи, найти
    // среднюю арифметическую оценку всех студентов

    const int iStudentsCount = 5;
    std::cout << "Enter 5 students, for each: name, score (to find average score)" << std::endl;

    CStudent* pStudents = new CStudent[iStudentsCount];

    for (int i = 0; i < iStudentsCount; i++)
    {
        std::cout << "Next student: " << std::endl;

        std::cin >> pStudents[i].m_cStudentName;
        std::cin >> pStudents[i].m_iScore;
    }

    std::cout << std::endl;

    CalculateArithmeticMean(pStudents, iStudentsCount);

    delete[] pStudents;
}

void ShowExcellentStudents(CStudent* pStudents, const int& iElementsCount)
{
    bool bExcellentStudentExists = false;

    for (int i = 0; i < iElementsCount; i++)
    {
        if (pStudents[i].m_iScore == 5)
        {
            std::cout << "Excellent student: " << pStudents[i].m_cStudentName << std::endl;
            bExcellentStudentExists = true;
        }
    }

    if (!bExcellentStudentExists)
        std::cout << "There is no excellent student" << std::endl;
}

void Exercise1()
{
    // Exercise1: Ввести информацию о студентах (имя и балл за экзамен)
    // и найти всех отличников

    const int iStudentsCount = 5;
    std::cout << "Enter 5 students, for each: name, score (to find excellent students)" << std::endl;

    CStudent* pStudents = new CStudent[iStudentsCount];

    for (int i = 0; i < iStudentsCount; i++)
    {
        std::cout << "Next student: " << std::endl;

        std::cin >> pStudents[i].m_cStudentName;
        std::cin >> pStudents[i].m_iScore;
    }

    std::cout << std::endl;

    ShowExcellentStudents(pStudents, iStudentsCount);

    delete[] pStudents;
}

void PrintEvenNumber(const int& iNumber)
{
    if (!iNumber)
        return;

    int iNum = iNumber%10;

    if (!(iNum%2))
        std::cout << iNum << " ";

    PrintEvenNumber(iNumber/10);
}

void ExerciseOnLesson1()
{
    // ExerciseOnLesson1: Написать рекурсивную функцию печати чётных цифр в числе (порядок любой):
    // Ввод: 32518432
    // Ответ: 2 4 8 2

    int iInput = 0;
    std::cout << "Enter int (print even numbers): " << std::endl;

    std::cin >> iInput;

    PrintEvenNumber(iInput);
}

int main()
{
//    ExerciseOnLesson1();
//    Exercise1();
//    Exercise2();
//    Exercise3();
//    Exercise4();
//    Exercise5();
//    Exercise6();
//    Exercise7();

    return 0;
}

