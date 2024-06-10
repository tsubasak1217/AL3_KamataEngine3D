#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "Easing.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"


//何もしない関数
void Void();

//================================================================
//                     ファイル操作の関数
//================================================================
std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath);

//================================================================
//                       時間の関数
//================================================================
//フレーム数を時間に換算する関数
/// <summary>
/// フレーム数を時間に換算する関数
/// </summary>
/// <param name="count">:フレーム数</param>
/// <param name="tranceMode">[0:秒][1:分][2:時間]</param>
/// <returns></returns>
int FrameToClock(int count, int tranceMode);

//================================================================
//                      数学的な関数
//================================================================

//長さを計る関数
float Length(const Vector2& pos1, const Vector2& pos2);
float Length(const Vector3& pos1, const Vector3& pos2);
float Length(float pos1x, float pos1y, float pos2x, float pos2y);
float Length(const Vector2& vec);
float Length(const Vector3& vec);

//ノーマライズ関数
Vector2 Normalize(const Vector2& pos1, const Vector2& pos2);
Vector3 Normalize(const Vector3& pos1, const Vector3& pos2);
Vector2 Normalize(const Vector2& vec);
Vector3 Normalize(const Vector3& vec);

//内積を求める
float Dot(const Vector2& pos1, const Vector2& pos2, const Vector2& targetPos);
float Dot(const Vector2& a, const Vector2& b);
float Dot(const Vector3& a, const Vector3& b);

//外積を求める関数
float Cross(
	float line1StartX, float line1StartY,
	float line1EndX, float line1EndY,
	float targetX, float targetY
);

float Cross(Vector2 pos1, Vector2 pos2, Vector2 targetPos);

//線と線の交点を求める関数
Vector2 CrossPos(
	Vector2 line1Pos1, Vector2 line1Pos2,
	Vector2 line2Pos1, Vector2 line2Pos2
);
Vector2 CrossPos2(Vector2 line1Pos1, Vector2 line1Pos2, Vector2 line2Pos1, Vector2 line2Pos2);

//線を平行移動する関数
Vector2 ShiftLine(Vector2 pos1, Vector2 pos2, float distance);
void ShiftLineCtrl(Vector2& pos1, Vector2& pos2, float distance);

// 負数を0に変換する関数
int negaZero(int num);
float negaZero(float num);

// clamp
int Clamp(int num, int min, int max);

// Lerp
Vector3 Slerp(const Vector3& startVec, const Vector3& endVec, float t);

//================================================================
//                      行列の計算関数
//================================================================

// -----------------加算------------------
Matrix2x2 Add(const Matrix2x2& matrix1, const Matrix2x2& matrix2);
Matrix3x3 Add(const Matrix3x3& matrix1, const Matrix3x3& matrix2);
Matrix4x4 Add(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

// -----------------減算------------------
Matrix2x2 Subtract(const Matrix2x2& matrix1, const Matrix2x2& matrix2);
Matrix3x3 Subtract(const Matrix3x3& matrix1, const Matrix3x3& matrix2);
Matrix4x4 Subtract(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

// ---------------積を求める----------------
Vector2 Multiply(const Vector2& vector, const Matrix2x2& matrix);
Vector2 Multiply(const Vector2& vector, const Matrix3x3& matrix);
Vector3 Multiply(const Vector3& vector, const Matrix4x4& matrix);
Matrix2x2 Multiply(const Matrix2x2& matrix1, const Matrix2x2& matrix2);
Matrix3x3 Multiply(const Matrix3x3& matrix1, const Matrix3x3& matrix2);
Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2);
// --------------スカラー倍----------------
Vector2 Multiply(const Vector2& vector, float scalar);
Vector3 Multiply(const Vector3& vector, float scalar);
Matrix2x2 Multiply(const Matrix2x2& matrix, float scalar);
Matrix3x3 Multiply(const Matrix3x3& matrix, float scalar);
Matrix4x4 Multiply(const Matrix4x4& matrix, float scalar);

// -----------------割り算------------------
Matrix2x2 Devide(const Matrix2x2& matrix, float devideNum);
Matrix3x3 Devide(const Matrix3x3& matrix, float devideNum);
Matrix4x4 Devide(const Matrix4x4& matrix, float devideNum);

// 同時座標系からデカルト座標系に変換する関数
Vector2 Transform(const Vector2& vector, const Matrix3x3& matrix);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 単位行列を返す関数
Matrix2x2 IdentityMat2();
Matrix3x3 IdentityMat3();
Matrix4x4 IdentityMat4();

// 拡大縮小行列を作る関数
Matrix3x3 ScaleMatrix(float scaleX, float scaleY);
Matrix3x3 ScaleMatrix(const Vector2& scale);
Matrix4x4 ScaleMatrix(float scaleX, float scaleY,float scaleZ);
Matrix4x4 ScaleMatrix(const Vector3& scale);

// 回転行列を作る関数
Matrix3x3 RotateMatrix(float theta);
Matrix4x4 RotateMatrix(const Vector3& rotate);

// 平行移動行列を作る関数
Matrix3x3 TranslateMatrix(float tx, float ty);
Matrix3x3 TranslateMatrix(const Vector2& t);
Matrix4x4 TranslateMatrix(float tx, float ty, float tz);
Matrix4x4 TranslateMatrix(const Vector3& t);

// アフィン変換行列を作る関数
Matrix3x3 AffineMatrix(Vector2 scale, float rotateTheta, Vector2 transLate);
Matrix4x4 AffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//逆行列を求める関数
Matrix2x2 InverseMatrix(const Matrix2x2& matrix);
Matrix3x3 InverseMatrix(const Matrix3x3& matrix);
Matrix4x4 InverseMatrix(const Matrix4x4& matrix);

//転置行列を求める関数
Matrix2x2 Transpose(const Matrix2x2& matrix);
Matrix3x3 Transpose(const Matrix3x3& matrix);
Matrix4x4 Transpose(const Matrix4x4& matrix);

//正射影行列を求める関数
Matrix3x3 OrthoMatrix(float left, float right, float top, float bottom);
Matrix4x4 OrthoMatrix(float left, float right, float top, float bottom,float znear,float zfar);

// 透視投影行列(視錐台)を求める関数
float AspectRatio(float windowWidth, float windowHeight);
Matrix4x4 PerspectiveMatrix(float fovY,float aspectRatio,float znear,float zfar);

//ビューポート変換行列を求める関数
Matrix3x3 ViewportMatrix(const Vector2& size, const Vector2& LeftTop);
Matrix4x4 ViewportMatrix(const Vector2& size, const Vector2& LeftTop,float minDepth,float maxDepth);

//レンダリングパイプライン作る関数
Matrix3x3 WvpVpMatrix(
	Vector2 playerPos, Vector2 playerScale, float playerAngle,
	Vector2 cameraPos, Vector2 cameraScale, float cameraAngle,
	Vector2 cameraRange, Vector2 leftTop,
	Vector2 screenSize
);

//行列の情報を表示する関数


//================================================================
//                     当たり判定関数
//================================================================

//回転していない矩形と円の当たり判定
bool IsHitBox_Ball(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius);
//回転していない矩形と円の当たり判定(当たった面を返す)
int IsHitBox_BallDirection(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius);

//================================================================
//                     オリジナル描画関数
//================================================================

// ---------------スプライン曲線の頂点計算用の関数---------------------
Vector2 Complement(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t);
Vector2 CatmullRom(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t);
Vector3 CatmullRom(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, float t);

void DrawSpline3D(std::list<Vector3>controlPoints, int32_t subdivision);

//================================================================
//                     色を扱う関数
//================================================================

//色の各成分を求める関数
int Red(int color);
int Green(int color);
int Blue(int color);
int Alpha(int color);

//色を変える関数
int ChangeColor(int startColor, int aimColor, float divideNum, float rate);
int ChangeColorT(int startColor, int aimColor, float t);

int GrayScale(int color);
