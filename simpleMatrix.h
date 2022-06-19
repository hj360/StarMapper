#ifndef SIMPLEMATRIX_H
#define SIMPLEMATRIX_H

#include <vector>
#include <cmath>
#include <iostream>

const double PI = 3.14159265;

static std::vector<std::vector<double>> MatrixMultiply(std::vector<std::vector<double>> &input_1, std::vector<std::vector<double>> &input_2)
{
    int input1_rows = input_1.size();
    int input1_cols = input_1[0].size();
    int input2_cols = input_2[0].size();
    int input2_rows = input_2.size();

    //Check if matrix can be multiplied
    if(input1_cols != input2_rows)
    {
        std::cerr << "Matrix Error! Cols != Rows" << std::endl;
        return std::vector<std::vector<double>> {};
    }

    //Initialize empty output matrix with output dimensions
    std::vector<std::vector<double>> outMatrix(input1_rows, std::vector<double>(input2_cols, 0));

    //Multiply rows by cols
    for(int i = 0; i < input1_rows; ++i)
    {
        for(int j = 0; j < input2_cols; ++j)
        {
            int sum = 0;
            for(int k = 0; k < input1_cols; ++k)
            {
                //Determine sum for each column * each row and add them for each col of output matrix
                sum += input_1[i][k] * input_2[k][j];
            }

            //Insert sum into output matrix
            outMatrix[i][j] = sum;
            
        }
    }

    return outMatrix;
}

static std::vector<std::vector<double>> Rotate_3D(std::vector<std::vector<double>> inputPoint, double angleX, double angleY, double angleZ)
{
    //Rotation Matricies
    std::vector<std::vector<double>> rotMatX = {{1, 0, 0}, {0, cos(angleX), -sin(angleX)}, {0, sin(angleX), cos(angleX)}};
    std::vector<std::vector<double>> rotMatY = {{cos(angleY), 0, sin(angleY)}, {0, 1, 0}, {-sin(angleY), 0, cos(angleY)}};
    std::vector<std::vector<double>> rotMatZ = {{cos(angleZ), -sin(angleZ), 0}, {sin(angleZ), cos(angleZ), 0}, {0, 0, 1}};
    //Convert degrees to radians
    angleX = angleX * PI/180;
    angleY = angleY * PI/180;
    angleY = angleY * PI/180;

    //Check if angle has been changed
    if(angleX != 0)
    {
        //Perform rotation
        inputPoint = MatrixMultiply(rotMatX, inputPoint);
    }

    if(angleY != 0)
    {
        inputPoint = MatrixMultiply(rotMatY, inputPoint);
    }

    if(angleZ != 0)
    {
        inputPoint = MatrixMultiply(rotMatZ, inputPoint);
    }

    return inputPoint;
}

static void Project_2D(std::vector<std::vector<double>> &inputPoint, std::vector<std::vector<double>> &outPoint)
{
    //Orthographic projection matrix
    std::vector<std::vector<double>> orthoMatrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    //Place point in 2D vector
    outPoint = MatrixMultiply(orthoMatrix, inputPoint);
}


#endif