#include <iostream>
#include <cmath> // only std::sqrt

struct CStudent
{
    char         m_cStudentName[20];
    unsigned int m_iScore;
};

struct CPoint
{
    double dX;
    double dY;
};

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

    return 0;
}

