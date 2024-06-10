#include "MyFunc.h"
#include "PrimitiveDrawer.h"

//何もしない関数
void Void() { ; }

//================================================================
//                     ファイル操作の関数
//================================================================
//csvを読み込む関数
std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath) {

	//最終結果を入れる配列
	std::vector<std::vector<int>> intArray;

	//ファイルの依り代、"file"
	std::ifstream file(csvFilePath);

	//ファイルの数値を入れる変数
	std::string line, value;

	// ファイルから読み取った1行をlineに格納 (改行区切り)
	while(std::getline(file, line)) {

		// 一行ごとの最終結果を入れる配列
		std::vector<int> row;

		// 1行ごとの文字列を入れる変数 (カンマ込み)
		std::istringstream issLine(line);

		/*issLineからカンマ区切りでデータを読み込みvalueに格納
		(行の値を1文字ずつに切り分ける)*/
		while(std::getline(issLine, value, ',')) {

			// 切り分けた一文字を char → int型に変換
			int intValue = atoi(value.c_str());

			// 行にint型の値を入れる
			row.push_back(intValue);
		}

		// std::vector<int>型の1行を配列に入れていく
		intArray.push_back(row);
	}

	return intArray;
}


//================================================================
//                       時間の関数
//================================================================
//フレーム数を時計に変換する関数
int FrameToClock(int count, int tranceMode) {

	int result = 0;
	enum TranceMode{
		Sec,
		Min,
		Hour
	};

	switch(tranceMode) {
	case Sec:
		result = count / 60;
		break;

	case Min:
		result = (count / 60) / 60;
		break;

	case Hour:
		result = ((count / 60) / 60) / 60;
		break;

	default:
		break;
	}

	return result;

};

//================================================================
//                      数学的な関数
//================================================================

//長さを求める関数
float Length(const Vector2& pos1, const Vector2& pos2) {
	float xLength = (pos1.x - pos2.x);
	float yLength = (pos1.y - pos2.y);
	return sqrtf(xLength * xLength + yLength * yLength);
}
float Length(const Vector3& pos1, const Vector3& pos2) {
	float xLength = (pos1.x - pos2.x);
	float yLength = (pos1.y - pos2.y);
	float zLength = (pos1.z - pos2.z);
	return sqrtf(xLength * xLength + yLength * yLength + zLength * zLength);
}
float Length(float pos1x, float pos1y, float pos2x, float pos2y) {
	float xLength = pos2x - pos1x;
	float yLength = pos2y - pos1y;
	return sqrtf(xLength * xLength + yLength * yLength);
}
float Length(const Vector2& vec) {
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}
float Length(const Vector3& vec) {
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

//ノーマライズ関数
Vector2 Normalize(const Vector2& pos1, const Vector2& pos2) {

	Vector2 vec = pos2 - pos1;

	if(float length = Length(vec)) {
		return vec / length;
	} else {
		return { 0.0f,0.0f };
	}
}
Vector3 Normalize(const Vector3& pos1, const Vector3& pos2) {
	Vector3 vec = pos2 - pos1;

	if(float length = Length(vec)) {
		return vec / length;
	} else {
		return { 0.0f,0.0f,0.0f };
	}
}
Vector2 Normalize(const Vector2& vec) {
	if(float length = Length(vec)) {
		return vec / length;
	} else {
		return { 0.0f,0.0f };
	}
}
Vector3 Normalize(const Vector3& vec) {
	if(float length = Length(vec)) {
		return vec / length;
	} else {
		return { 0.0f,0.0f,0.0f };
	}
}

//内積を求める関数
float Dot(const Vector2& pos1, const Vector2& pos2, const Vector2& targetPos) {

	Vector2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	float lineLength = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
	Vector2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return ((lineVector.x * forTarget.x) + (lineVector.y * forTarget.y)) / lineLength;
}

float Dot(const Vector2& a, const Vector2& b) {
	return (a.x * b.x) + (a.y * b.y);
}

float Dot(const Vector3& a, const Vector3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
};

//外積を求める関数
float Cross(
	float lineStartX, float lineStartY,
	float lineEndX, float lineEndY,
	float targetX, float targetY
) {
	float lineLengthX = lineEndX - lineStartX;
	float lineLengthY = lineEndY - lineStartY;
	float lineLength = sqrtf(lineLengthX * lineLengthX + lineLengthY * lineLengthY);

	float line2TargetX = targetX - lineStartX;
	float line2TargetY = targetY - lineStartY;

	return ((lineLengthX * line2TargetY) - (lineLengthY * line2TargetX)) / lineLength;
}

float Cross(Vector2 pos1, Vector2 pos2, Vector2 targetPos) {
	Vector2 lineVector = { pos2.x - pos1.x,pos2.y - pos1.y };
	float lineLength = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
	Vector2 forTarget = { targetPos.x - pos1.x,targetPos.y - pos1.y };

	return ((lineVector.x * forTarget.y) - (lineVector.y * forTarget.x)) / lineLength;
}

// ベクトルの交点を求める関数
Vector2 CrossPos(Vector2 line1Pos1, Vector2 line1Pos2, Vector2 line2Pos1, Vector2 line2Pos2) {
	float s1 =
		((line2Pos2.x - line2Pos1.x) * (line1Pos1.y - line2Pos1.y) -
			(line2Pos2.y - line2Pos1.y) * (line1Pos1.x - line2Pos1.x)) / 2.0f;

	float s2 =
		((line2Pos2.x - line2Pos1.x) * (line2Pos1.y - line1Pos2.y) -
			(line2Pos2.y - line2Pos1.y) * (line2Pos1.x - line1Pos2.x)) / 2.0f;

	Vector2 crossPos = {
		line1Pos1.x + (line1Pos2.x - line1Pos1.x) * s1 / (s1 + s2),
		line1Pos1.y + (line1Pos2.y - line1Pos1.y) * s1 / (s1 + s2)
	};

	return crossPos;
}

Vector2 CrossPos2(Vector2 line1Pos1, Vector2 line1Pos2, Vector2 line2Pos1, Vector2 line2Pos2) {
	float s1 =
		((line2Pos2.x - line2Pos1.x) * (line1Pos1.y - line2Pos1.y) -
			(line2Pos2.y - line2Pos1.y) * (line1Pos1.x - line2Pos1.x)) / 2.0f;

	float s2 =
		((line2Pos2.x - line2Pos1.x) * (line2Pos1.y - line1Pos2.y) -
			(line2Pos2.y - line2Pos1.y) * (line2Pos1.x - line1Pos2.x)) / 2.0f;

	Vector2 crossPos = { 0.0f,0.0f };

	if(s1 != 0 && s2 != 0) {
		crossPos = {
			line1Pos1.x + (line1Pos2.x - line1Pos1.x) * s1 / (s1 + s2),
			line1Pos1.y + (line1Pos2.y - line1Pos1.y) * s1 / (s1 + s2)
		};
	} else {
		crossPos = line1Pos1;
	}

	return crossPos;
}

// 線を平行移動する関数
Vector2 ShiftLine(Vector2 pos1, Vector2 pos2, float distance) {

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float length = sqrtf(dx * dx + dy * dy);
	float normalizedX = dx / length;
	float normalizedY = dy / length;

	return{
	normalizedY * distance,
	-normalizedX * distance
	};
}
void ShiftLineCtrl(Vector2& pos1, Vector2& pos2, float distance) {

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float length = sqrtf(dx * dx + dy * dy);
	float normalizedX = dx / length;
	float normalizedY = dy / length;

	Vector2 pos = {
	normalizedY * distance,
	-normalizedX * distance
	};

	pos1 = pos1.operator+(pos);
	pos2 = pos2.operator+(pos);
}

// 負数を0に変換する関数
int negaZero(int num) {
	return (num < 0) ? 0 : num;
}

float negaZero(float num) {
	return (num < 0) ? 0 : num;
}

int Clamp(int num, int min, int max){

	if(num < min){ return min; }
	if(num > max){ return max; }
	return num;
}

Vector3 Slerp(const Vector3& startVec, const Vector3& endVec, float t)
{
	// 正規化する
	Vector3 start = Normalize(startVec);
	Vector3 end = Normalize(endVec);

	float cos = std::clamp(Dot(start, end), -1.0f, 1.0f);// 正規化ベクトル同士の内積なのでcosθの値が出る
	float theta = std::acos(cos);// cosθからθを算出
	float sin = std::sin(theta);// sinθの値を計算

	// sinが0の場合、startとendが同じベクトルであるのでリターン
	if(sin == 0.0f){ return start; }

	t = std::clamp(t, 0.0f, 1.0f);// 媒介変数を0~1に収める

	// 補完ベクトルを求める
	start = start * (std::sin(theta * (1.0f - t)) / sin);
	end = end * (std::sin(theta * t) / sin);

	return start + end;
}

//================================================================
//                        行列関数
//================================================================

// 加算
Matrix2x2 Add(const Matrix2x2& matrix1, const Matrix2x2& matrix2) {

	Matrix2x2 result;

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
};
Matrix3x3 Add(const Matrix3x3& matrix1, const Matrix3x3& matrix2) {

	Matrix3x3 result;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
}

Matrix4x4 Add(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {

	Matrix4x4 result;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
}

// 減算
Matrix2x2 Subtract(const Matrix2x2& matrix1, const Matrix2x2& matrix2) {

	Matrix2x2 result;

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
};
Matrix3x3 Subtract(const Matrix3x3& matrix1, const Matrix3x3& matrix2) {

	Matrix3x3 result;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
};

Matrix4x4 Subtract(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {

	Matrix4x4 result;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
};

// -----------------割り算------------------
Matrix2x2 Devide(const Matrix2x2& matrix, float devideNum) {
	Matrix2x2 result;

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			result.m[i][j] = matrix.m[i][j] / devideNum;
		}
	}

	return result;
};

Matrix3x3 Devide(const Matrix3x3& matrix, float devideNum) {

	Matrix3x3 result;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result.m[i][j] = matrix.m[i][j] / devideNum;
		}
	}

	return result;
}

Matrix4x4 Devide(const Matrix4x4& matrix, float devideNum) {

	Matrix4x4 result;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[i][j] / devideNum;
		}
	}

	return result;
};

// ---------------積を求める----------------
Vector2 Multiply(const Vector2& vector, const Matrix2x2& matrix) {

	return {
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1]
	};
};
Vector2 Multiply(const Vector2& vector, const Matrix3x3& matrix) {
	Vector2 result;
	float w;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

	assert(w != 0);

	result.x /= w;
	result.y /= w;

	return result;
}

Vector3 Multiply(const Vector3& vector, const Matrix4x4& matrix) {

	Vector3 result;
	float w;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;

};

Matrix2x2 Multiply(const Matrix2x2& matrix1, const Matrix2x2& matrix2) {

	Matrix2x2 result;

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {

			result.m[i][j] =
				(matrix1.m[i][0] * matrix2.m[0][j]) +
				(matrix1.m[i][1] * matrix2.m[1][j]);
		}
	}

	return result;
};
Matrix3x3 Multiply(const Matrix3x3& matrix1, const Matrix3x3& matrix2) {

	Matrix3x3 result;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {

			result.m[i][j] =
				(matrix1.m[i][0] * matrix2.m[0][j]) +
				(matrix1.m[i][1] * matrix2.m[1][j]) +
				(matrix1.m[i][2] * matrix2.m[2][j]);
		}
	}

	return result;
}

Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {

	Matrix4x4 result;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {

			result.m[i][j] =
				(matrix1.m[i][0] * matrix2.m[0][j]) +
				(matrix1.m[i][1] * matrix2.m[1][j]) +
				(matrix1.m[i][2] * matrix2.m[2][j]) +
				(matrix1.m[i][3] * matrix2.m[3][j]);
		}
	}

	return result;
}

// --------------スカラー倍----------------
Vector2 Multiply(const Vector2& vector, float scalar) {
	return { vector.x * scalar,vector.y * scalar };
}
Vector3 Multiply(const Vector3& vector, float scalar) {
	return { vector.x * scalar,vector.y * scalar,vector.z * scalar };
}
Matrix2x2 Multiply(const Matrix2x2& matrix, float scalar) {

	Matrix2x2 result;
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			result.m[i][j] = matrix.m[i][j] * scalar;
		}
	}

	return result;
}
Matrix3x3 Multiply(const Matrix3x3& matrix, float scalar) {

	Matrix3x3 result;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			result.m[i][j] = matrix.m[i][j] * scalar;
		}
	}

	return result;
}
Matrix4x4 Multiply(const Matrix4x4& matrix, float scalar) {

	Matrix4x4 result;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[i][j] * scalar;
		}
	}

	return result;
}

// 同時座標系からデカルト座標系に変換する関数
Vector2 Transform(const Vector2& vector, const Matrix3x3& matrix) {
	Vector2 result;
	float w;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + matrix.m[2][1];
	w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + matrix.m[2][2];

	assert(w != 0);

	result.x /= w;
	result.y /= w;

	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	float w;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

// 単位行列を返す関数
Matrix2x2 IdentityMat2() {

	Matrix2x2 identity(
		1.0f, 0.0f,
		0.0f, 1.0f
	);

	return identity;
}

Matrix3x3 IdentityMat3() {

	Matrix3x3 identity(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	return identity;
}

Matrix4x4 IdentityMat4() {

	Matrix4x4 identity(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return identity;
}

/*------------------------- 拡大縮小行列を作る関数 --------------------------*/
Matrix3x3 ScaleMatrix(float scaleX, float scaleY) {
	Matrix3x3 matrix;
	matrix.m[0][0] = scaleX;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = scaleY;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;

	return matrix;
}

Matrix3x3 ScaleMatrix(const Vector2& scale) {
	Matrix3x3 matrix;
	matrix.m[0][0] = scale.x;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = scale.y;
	matrix.m[1][2] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = 1;

	return matrix;
}

Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ) {
	Matrix4x4 matrix;
	matrix.m[0][0] = scaleX;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = scaleY;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = scaleZ;
	matrix.m[2][3] = 0;

	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = 0;
	matrix.m[3][3] = 1;

	return matrix;
}

Matrix4x4 ScaleMatrix(const Vector3& scale) {
	Matrix4x4 matrix;
	matrix.m[0][0] = scale.x;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = scale.y;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = scale.z;
	matrix.m[2][3] = 0;

	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = 0;
	matrix.m[3][3] = 1;

	return matrix;
}

/*------------------------- 回転行列を作る関数 --------------------------*/
Matrix3x3 RotateMatrix(float theta) {

	Matrix3x3 result;
	result.m[0][0] = std::cos(theta);
	result.m[0][1] = std::sin(theta);
	result.m[0][2] = 0.0f;

	result.m[1][0] = -std::sin(theta);
	result.m[1][1] = std::cos(theta);
	result.m[1][2] = 0.0f;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;

	return result;
}

Matrix4x4 RotateMatrix(const Vector3& rotate) {
	Matrix4x4 rotateMat[3];

	/*-------X軸の回転行列-------*/
	if(rotate.x) {

		float sin = std::sin(rotate.x);
		float cos = std::cos(rotate.x);

		rotateMat[0].m[0][0] = 1;
		rotateMat[0].m[1][0] = 0;
		rotateMat[0].m[2][0] = 0;
		rotateMat[0].m[3][0] = 0;

		rotateMat[0].m[0][1] = 0;
		rotateMat[0].m[1][1] = cos;
		rotateMat[0].m[2][1] = -sin;
		rotateMat[0].m[3][1] = 0;

		rotateMat[0].m[0][2] = 0;
		rotateMat[0].m[1][2] = sin;
		rotateMat[0].m[2][2] = cos;
		rotateMat[0].m[3][2] = 0;

		rotateMat[0].m[0][3] = 0;
		rotateMat[0].m[1][3] = 0;
		rotateMat[0].m[2][3] = 0;
		rotateMat[0].m[3][3] = 1;
	} else {
		rotateMat[0] = IdentityMat4();
	}

	/*-------Y軸の回転行列-------*/
	if(rotate.y) {

		float sin = std::sin(rotate.y);
		float cos = std::cos(rotate.y);

		rotateMat[1].m[0][0] = cos;
		rotateMat[1].m[1][0] = 0;
		rotateMat[1].m[2][0] = sin;
		rotateMat[1].m[3][0] = 0;

		rotateMat[1].m[0][1] = 0;
		rotateMat[1].m[1][1] = 1;
		rotateMat[1].m[2][1] = 0;
		rotateMat[1].m[3][1] = 0;

		rotateMat[1].m[0][2] = -sin;
		rotateMat[1].m[1][2] = 0;
		rotateMat[1].m[2][2] = cos;
		rotateMat[1].m[3][2] = 0;

		rotateMat[1].m[0][3] = 0;
		rotateMat[1].m[1][3] = 0;
		rotateMat[1].m[2][3] = 0;
		rotateMat[1].m[3][3] = 1;
	} else {
		rotateMat[1] = IdentityMat4();
	}

	/*-------Z軸の回転行列-------*/
	if(rotate.z) {

		float sin = std::sin(rotate.z);
		float cos = std::cos(rotate.z);

		rotateMat[2].m[0][0] = cos;
		rotateMat[2].m[1][0] = -sin;
		rotateMat[2].m[2][0] = 0;
		rotateMat[2].m[3][0] = 0;

		rotateMat[2].m[0][1] = sin;
		rotateMat[2].m[1][1] = cos;
		rotateMat[2].m[2][1] = 0;
		rotateMat[2].m[3][1] = 0;

		rotateMat[2].m[0][2] = 0;
		rotateMat[2].m[1][2] = 0;
		rotateMat[2].m[2][2] = 1;
		rotateMat[2].m[3][2] = 0;

		rotateMat[2].m[0][3] = 0;
		rotateMat[2].m[1][3] = 0;
		rotateMat[2].m[2][3] = 0;
		rotateMat[2].m[3][3] = 1;
	} else {
		rotateMat[2] = IdentityMat4();
	}

	return Multiply(rotateMat[0], Multiply(rotateMat[1], rotateMat[2]));
}

/*------------------------- 平行移動行列を作る関数 --------------------------*/
Matrix3x3 TranslateMatrix(float tx, float ty) {
	Matrix3x3 matrix;
	matrix.m[0][0] = 1;  matrix.m[0][1] = 0;  matrix.m[0][2] = 0;
	matrix.m[1][0] = 0;  matrix.m[1][1] = 1;  matrix.m[1][2] = 0;
	matrix.m[2][0] = tx; matrix.m[2][1] = ty; matrix.m[2][2] = 1;
	return matrix;
}

Matrix3x3 TranslateMatrix(const Vector2& t) {
	Matrix3x3 matrix;
	matrix.m[0][0] = 1;   matrix.m[0][1] = 0;   matrix.m[0][2] = 0;
	matrix.m[1][0] = 0;   matrix.m[1][1] = 1;   matrix.m[1][2] = 0;
	matrix.m[2][0] = t.x; matrix.m[2][1] = t.y; matrix.m[2][2] = 1;
	return matrix;
}

Matrix4x4 TranslateMatrix(float tx, float ty, float tz) {
	Matrix4x4 matrix;
	matrix.m[0][0] = 1;  matrix.m[0][1] = 0;  matrix.m[0][2] = 0;  matrix.m[0][3] = 0;
	matrix.m[1][0] = 0;  matrix.m[1][1] = 1;  matrix.m[1][2] = 0;  matrix.m[1][3] = 0;
	matrix.m[2][0] = 0;  matrix.m[2][1] = 0;  matrix.m[2][2] = 1;  matrix.m[2][3] = 0;
	matrix.m[3][0] = tx; matrix.m[3][1] = ty; matrix.m[3][2] = tz; matrix.m[3][3] = 1;
	return matrix;
}

Matrix4x4 TranslateMatrix(const Vector3& t) {
	Matrix4x4 matrix;
	matrix.m[0][0] = 1;   matrix.m[0][1] = 0;   matrix.m[0][2] = 0;   matrix.m[0][3] = 0;
	matrix.m[1][0] = 0;   matrix.m[1][1] = 1;   matrix.m[1][2] = 0;   matrix.m[1][3] = 0;
	matrix.m[2][0] = 0;   matrix.m[2][1] = 0;   matrix.m[2][2] = 1;   matrix.m[2][3] = 0;
	matrix.m[3][0] = t.x; matrix.m[3][1] = t.y; matrix.m[3][2] = t.z; matrix.m[3][3] = 1;
	return matrix;
}


/*------------------------- アフィン行列を作る関数 --------------------------*/
Matrix3x3 AffineMatrix(Vector2 scale, float rotateTheta, Vector2 translate) {

	Matrix3x3 matrix;
	matrix.m[0][0] = scale.x * cosf(rotateTheta);
	matrix.m[0][1] = scale.x * sinf(rotateTheta);
	matrix.m[0][2] = 0;

	matrix.m[1][0] = scale.y * -sinf(rotateTheta);
	matrix.m[1][1] = scale.y * cosf(rotateTheta);
	matrix.m[1][2] = 0;

	matrix.m[2][0] = translate.x;
	matrix.m[2][1] = translate.y;
	matrix.m[2][2] = 1;

	return matrix;
}

Matrix4x4 AffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 matrix(Multiply(ScaleMatrix(scale), RotateMatrix(rotate)));
	matrix.m[3][0] = translate.x;
	matrix.m[3][1] = translate.y;
	matrix.m[3][2] = translate.z;
	return matrix;
}

// 正則行列かどうか確認する関数--------------------------------------
// 3x3 行列の行列式を計算する関数
float Determinant3x3(const Matrix3x3& mat) {
	return
		(mat.m[0][0] * mat.m[1][1] * mat.m[2][2]) +
		(mat.m[0][1] * mat.m[1][2] * mat.m[2][0]) +
		(mat.m[0][2] * mat.m[1][0] * mat.m[2][1]) -
		(mat.m[0][2] * mat.m[1][1] * mat.m[2][0]) -
		(mat.m[0][1] * mat.m[1][0] * mat.m[2][2]) -
		(mat.m[0][0] * mat.m[1][2] * mat.m[2][1]);
}

// 4x4 行列の行列式を計算する関数
float Determinant4x4(const Matrix4x4& mat) {
	float det = 0.0f;
	for(int i = 0; i < 4; i++) {

		Matrix3x3 minor;

		for(int j = 0; j < 3; j++) {
			int k = 0;
			for(int l = 0; l < 4; l++) {
				if(l != i) {
					minor.m[j][k++] = mat.m[j + 1][l];
				}
			}
		}

		float subDet = Determinant3x3(minor);
		det += (i % 2 == 0 ? 1.0f : -1.0f) * mat.m[0][i] * subDet;
	}
	return det;
}

//逆行列を求める関数
Matrix2x2 InverseMatrix(const Matrix2x2& matrix) {

	float det = (matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[0][1] * matrix.m[1][0]);
	assert(det != 0);


	Matrix2x2 result;
	result.m[0][0] = matrix.m[1][1];
	result.m[0][1] = -matrix.m[0][1];

	result.m[1][0] = -matrix.m[1][0];
	result.m[1][1] = matrix.m[0][0];

	return Devide(result, det);
};

Matrix3x3 InverseMatrix(const Matrix3x3& matrix) {

	float det =
		(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) +
		(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +
		(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -
		(matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) -
		(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	assert(det != 0);

	Matrix3x3 result;
	result.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0];
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	result.m[2][0] = matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0];
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];

	return Devide(result, det);
}

Matrix4x4 InverseMatrix(const Matrix4x4& matrix) {

	Matrix4x4 inv;
	float sweep[4][8];

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			// sweepの左側に逆行列を求める行列をセット
			sweep[i][j] = matrix.m[i][j];

			// sweepの右半分は単位行列で初期化
			sweep[i][4 + j] = (i == j) ? 1.0f : 0.0f;
		}
	}

	// 左半分が単位行列になるまで繰り返す (右半分に逆行列が求められる)
	for(int col = 0; col < 4; col++) {

		/*------------------------------------------------------*/
		/*				       	ソート、除外						*/
		/*------------------------------------------------------*/

		/* 最大の絶対値を注目対角成分の絶対値と仮定 */
		float max = fabs(sweep[col][col]);
		int maxIdx = col;

		// 今見ている対角成分より大きい絶対値を持つ要素がその列のその行より後にあるか探す
		for(int row = col + 1; row < 4; row++) {
			if(fabs(sweep[row][col]) > max) {
				max = fabs(sweep[row][col]);
				maxIdx = row;
			}
		}

		// 最大値が0の場合、逆行列は求められない
		assert(fabs(sweep[maxIdx][col]) > 0);

		// 見つかった場合、その要素が見つかった行と今の行の要素を入れ替える
		if(col != maxIdx) {
			for(int col2 = 0; col2 < 8; col2++) {
				std::swap(sweep[maxIdx][col2], sweep[col][col2]);
			}
		}

		/*------------------------------------------------------*/
		/*				       	逆行列の計算						*/
		/*------------------------------------------------------*/

		/*--------- 今見ている列の対角成分を1にする ---------*/

		// 対角成分 sweep[col][col]に掛けると1になる値を求める
		float x = 1.0f / sweep[col][col];

		for(int col2 = 0; col2 < 8; col2++) {
			// この計算でsweep[col][col]が1になる 
			// (対角成分以外にもその行すべての要素に掛ける。)
			sweep[col][col2] *= x;
		}

		/*------- 今見ている列の対角成分以外を0にする -------*/
		for(int row = 0; row < 4; row++) {

			if(row == col) { continue; }// 対角成分はそのまま

			// 対角成分のある行以外に掛ける値を求める
			x = -sweep[row][col];

			for(int col2 = 0; col2 < 8; col2++) {
				// 対角成分を1にした行をa倍して足していく
				// すると対角成分以外のsweep[row][col]が0になる ( 自分に対して 1 x -自分 を足しているため。)
				sweep[row][col2] += sweep[col][col2] * x;
			}
		}
	}

	// sweepの右半分がmatrixの逆行列
	for(int row = 0; row < 4; row++) {
		for(int col = 0; col < 4; col++) {
			inv.m[row][col] = sweep[row][4 + col];
		}
	}

	return inv;
};

//転置行列を求める関数
Matrix2x2 Transpose(const Matrix2x2& matrix) {

	Matrix2x2 result;
	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];

	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];

	return result;
};

Matrix3x3 Transpose(const Matrix3x3& matrix) {

	Matrix3x3 result;
	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];
	result.m[0][2] = matrix.m[2][0];

	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];
	result.m[1][2] = matrix.m[2][1];

	result.m[2][0] = matrix.m[0][2];
	result.m[2][1] = matrix.m[1][2];
	result.m[2][2] = matrix.m[2][2];

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& matrix) {
	Matrix4x4 result;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}
	return result;
}


//正射影行列を求める関数
Matrix3x3 OrthoMatrix(float left, float right, float top, float bottom) {

	Matrix3x3 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;

	return result;
}

Matrix4x4 OrthoMatrix(float left, float right, float top, float bottom, float znear, float zfar) {

	Matrix4x4 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1.0f / (zfar - znear);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = znear / (znear - zfar);
	result.m[3][3] = 1;

	return result;
}

float AspectRatio(float windowWidth, float windowHeight) {
	return windowHeight / windowWidth;
}

Matrix4x4 PerspectiveMatrix(float fovY, float aspectRatio, float znear, float zfar) {

	Matrix4x4 result;

	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2.0f));
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1.0f / std::tan(fovY / 2.0f);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = zfar / (zfar - znear);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = (-znear * zfar) / (zfar - znear);
	result.m[3][3] = 0;

	return result;
}

//ビューポート変換行列を求める関数
Matrix3x3 ViewportMatrix(const Vector2& size, const Vector2& LeftTop) {

	Matrix3x3 result;

	result.m[0][0] = size.x * 0.5f;
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(size.y * 0.5f);
	result.m[1][2] = 0;

	result.m[2][0] = LeftTop.x + (size.x * 0.5f);
	result.m[2][1] = LeftTop.y + (size.y * 0.5f);
	result.m[2][2] = 1;

	return result;
}

Matrix4x4 ViewportMatrix(const Vector2& size, const Vector2& LeftTop, float minDepth, float maxDepth) {

	Matrix4x4 result;

	result.m[0][0] = size.x * 0.5f;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -(size.y * 0.5f);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = LeftTop.x + (size.x * 0.5f);
	result.m[3][1] = LeftTop.y + (size.y * 0.5f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}
;


//レンダリングパイプライン作る関数
Matrix3x3 WvpVpMatrix(
	Vector2 playerPos, Vector2 playerScale, float playerAngle,
	Vector2 cameraPos, Vector2 cameraScale, float cameraAngle,
	Vector2 cameraRange, Vector2 leftTop,
	Vector2 screenSize
) {

	Matrix3x3 worldMatrix;
	Matrix3x3 cameraMatrix;
	Matrix3x3 viewMatrix;
	Matrix3x3 orthoMatrix;
	Matrix3x3 viewPortMatrix;
	Matrix3x3 result;

	worldMatrix = AffineMatrix(playerScale, playerAngle, playerPos);//プレイヤーのワールド行列
	cameraMatrix = AffineMatrix(cameraScale, cameraAngle, cameraPos);
	viewMatrix = InverseMatrix(cameraMatrix);//カメラの逆行列
	orthoMatrix = OrthoMatrix(//正射影行列
		-(cameraRange.x * 0.5f),
		cameraRange.x * 0.5f,
		-(cameraRange.y * 0.5f),
		cameraRange.y * 0.5f
	);
	viewPortMatrix = ViewportMatrix(//ビューポート行列
		screenSize, leftTop
	);

	//行列の合成
	result = Multiply(worldMatrix, viewMatrix);
	result = Multiply(result, orthoMatrix);
	result = Multiply(result, viewPortMatrix);

	return result;
}

//================================================================
//                        行列の表示の関数
//================================================================



//================================================================
//                     当たり判定関数
//================================================================

//回転していない矩形と円の当たり判定
bool IsHitBox_Ball(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius) {

	float distX = ballPos.x - boxCenter.x;
	float distY = ballPos.y - boxCenter.y;

	if(distX >= -boxSize.x / 2.0f && distX <= boxSize.x / 2.0f) {

		if(distY >= (-boxSize.y / 2.0f) - ballRasius && distY <= (boxSize.y / 2.0f) + ballRasius) {

			return true;

		} else {
			return false;
		}

	} else if(distY >= -boxSize.y / 2.0f && distY <= boxSize.y / 2.0f) {

		if(distX >= (-boxSize.x / 2.0f) - ballRasius && distX <= (boxSize.x / 2.0f) + ballRasius) {
			return true;

		} else {
			return false;
		}

	} else {

		if(distX < 0 && distY < 0) {
			if(
				Length(boxCenter.x - boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}
		} else if(distX >= 0 && distY < 0) {
			if(
				Length(boxCenter.x + boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}

		} else if(distX < 0 && distY >= 0) {
			if(
				Length(boxCenter.x - boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}

		} else {
			if(
				Length(boxCenter.x + boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {
				return true;
			} else {
				return false;
			}
		}
	}
}
//回転していない矩形と円の当たり判定(当たった面を返す)
int IsHitBox_BallDirection(Vector2 boxCenter, Vector2 ballPos, Vector2 boxSize, float ballRasius) {

	float distX = ballPos.x - boxCenter.x;
	float distY = ballPos.y - boxCenter.y;

	if(distX >= -boxSize.x / 2.0f && distX <= boxSize.x / 2.0f) {

		if(distY >= (-boxSize.y / 2.0f) - ballRasius && distY <= (boxSize.y / 2.0f) + ballRasius) {

			if(distY >= 0) {
				return 1;//上面に当たった
			} else {
				return 3;//下面に当たった
			}

		} else {
			return false;
		}

	} else if(distY >= -boxSize.y / 2.0f && distY <= boxSize.y / 2.0f) {

		if(distX >= (-boxSize.x / 2.0f) - ballRasius && distX <= (boxSize.x / 2.0f) + ballRasius) {

			if(distX >= 0) {
				return 2;//右面に当たった
			} else {
				return 4;//左面に当たった
			}

		} else {
			return false;
		}

	} else {

		if(distX < 0 && distY >= 0) {//左上
			if(Length(boxCenter.x - boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if(sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 1;//上面に当たった
				} else {
					return 4;//左面に当たった
				}

			} else {
				return false;
			}
		} else if(distX >= 0 && distY >= 0) {//右上
			if(Length(boxCenter.x + boxSize.x / 2.0f, boxCenter.y + boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if(sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 1;//上面に当たった
				} else {
					return 2;//右面に当たった
				}

			} else {
				return false;
			}

		} else if(distX < 0 && distY < 0) {//左下
			if(Length(boxCenter.x - boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if(sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 3;//上面に当たった
				} else {
					return 4;//左面に当たった
				}

			} else {
				return false;
			}

		} else {//右下
			if(Length(boxCenter.x + boxSize.x / 2.0f, boxCenter.y - boxSize.y / 2.0f, ballPos.x, ballPos.y) <= ballRasius) {

				if(sqrtf(powf(distX, 2.0f)) < sqrtf(powf(distY, 2.0f))) {
					return 3;//上面に当たった
				} else {
					return 2;//左面に当たった
				}

			} else {
				return false;
			}
		}
	}
}

//================================================================
//                     描画に関わる関数
//================================================================

// ---------------スプライン曲線の頂点計算用の関数---------------------
Vector2 Complement(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t) {
	return(
		(p1.operator*(-1.0f) + p2.operator*(3.0f) - p3.operator*(3.0f) + p4).operator*(t * t * t) +
		(p1.operator*(2.0f) - p2.operator*(5.0f) + p3.operator*(4.0f) - p4).operator*(t * t) +
		(p1.operator*(-1.0f) + p3).operator*(t) +
		p2.operator*(2.0f)
		).operator*(0.5f);
}

Vector2 CatmullRom(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, float t) {

	t = std::clamp(t, 0.0f, 1.0f);// tを0~1に収める

	if(t >= 0.0f && t < 0.33f) {// 1/3
		return Complement(p1, p1, p2, p3, t / 0.33f);

	} else if(t >= 0.33f && t < 0.66f) {// 2/3
		return Complement(p1, p2, p3, p4, (t - 0.33f) / 0.33f);

	} else {// 3/3
		return Complement(p2, p3, p4, p4, (t - 0.66f) / 0.34f);
	}
}


Vector3 CatmullRom(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, float t){

	t = std::clamp(t, 0.0f, 1.0f);// tを0~1に収める

	// 二次元の平面に分解
	Vector2 xy[4] = {
		{p1.x,p1.y},
		{p2.x,p2.y},
		{p3.x,p3.y},
		{p4.x,p4.y}
	};

	Vector2 zy[4] = {
		{p1.z,p1.y},
		{p2.z,p2.y},
		{p3.z,p3.y},
		{p4.z,p4.y}
	};

	// 結果を格納す変数
	Vector2 xyResult;
	Vector2 zyResult;
	Vector3 result;

	// tの値に応じて座標を計算
	if(t >= 0.0f && t < 0.33f) {// 1/3
		xyResult = Complement(xy[0], xy[0], xy[1], xy[2], t / 0.33f);
		zyResult = Complement(zy[0], zy[0], zy[1], zy[2], t / 0.33f);

	} else if(t >= 0.33f && t < 0.66f) {// 2/3
		xyResult = Complement(xy[0], xy[1], xy[2], xy[3], (t - 0.33f) / 0.33f);
		zyResult = Complement(zy[0], zy[1], zy[2], zy[3], (t - 0.33f) / 0.33f);

	} else {// 3/3
		xyResult = Complement(xy[1], xy[2], xy[3], xy[3], (t - 0.66f) / 0.34f);
		zyResult = Complement(zy[1], zy[2], zy[3], zy[3], (t - 0.66f) / 0.34f);
	}

	// 三次元にする
	result = { xyResult.x,xyResult.y,zyResult.x };

	return result;
}

Vector3 CatmullRom(const std::vector<Vector3>& controlPoints, float t){

	t = std::clamp(t, 0.0f, 1.0f);// tを0~1に収める

	Vector3 result;
	std::vector<Vector3> tmpControlPoints = controlPoints;
	// 要素数が必要数に達するまでコピーして追加
	while(tmpControlPoints.size() < 4){
		tmpControlPoints.push_back(tmpControlPoints.back());
	}

	int size = int(tmpControlPoints.size() - 1);
	float width = 1.0f / size;
	float t2 = std::fmod(t, width) / width;
	int idx = int(t / width);

	result = PrimaryCatmullRom(
		tmpControlPoints[Clamp(idx - 1, 0, size)],
		tmpControlPoints[idx],
		tmpControlPoints[Clamp(idx + 1, 0, size)],
		tmpControlPoints[Clamp(idx + 2, 0, size)],
		t2
	);

	return result;
}

Vector3 PrimaryCatmullRom(const Vector3& p1, const Vector3& p2, const Vector3& p3, const Vector3& p4, float t){
	t = std::clamp(t, 0.0f, 1.0f);// tを0~1に収める
	Vector2 xyResult;
	Vector2 zyResult;
	Vector3 result;

	// 二次元の平面に分解
	Vector2 xy[4] = {
		{p1.x,p1.y},
		{p2.x,p2.y},
		{p3.x,p3.y},
		{p4.x,p4.y}
	};

	Vector2 zy[4] = {
		{p1.z,p1.y},
		{p2.z,p2.y},
		{p3.z,p3.y},
		{p4.z,p4.y}
	};

	xyResult = Complement(xy[0], xy[1], xy[2], xy[3], t);
	zyResult = Complement(zy[0], zy[1], zy[2], zy[3], t);
	// 三次元にする
	result = { xyResult.x,xyResult.y,zyResult.x };

	return result;
}

void DrawSpline3D(const std::vector<Vector3>& controlPoints, int32_t subdivision){

	std::vector<Vector3>drawPoints;
	std::vector<Vector3> tmpControlPoints = controlPoints;
	int size = int(tmpControlPoints.size() - 1);

	// 要素数が必要数に達するまでコピーして追加
	while(tmpControlPoints.size() < 4){
		tmpControlPoints.push_back(tmpControlPoints.back());
	}

	// 4点ずつ見ていく
	for(int idx = 0; idx <= size; idx++){
		for(int32_t j = 0; j <= subdivision; j++){

			float t = float(j) / float(subdivision);

			drawPoints.push_back(
				PrimaryCatmullRom(
					tmpControlPoints[Clamp(idx - 1,0,size)],
					tmpControlPoints[idx],
					tmpControlPoints[Clamp(idx + 1,0,size)],
					tmpControlPoints[Clamp(idx + 2,0,size)],
					t
				)
			);
		}
	}

	// 描画
	for(int32_t i = 0; i < drawPoints.size() - 1; i++){
		PrimitiveDrawer::GetInstance()->DrawLine3d(drawPoints[i], drawPoints[i + 1], { 1.0f,0.0f,0.0f,1.0f });
	}
}


//================================================================
//                     色を扱う関数
//================================================================

//色の各要素を求める関数
int Red(int color) { return (color >> 24) & 0xFF; }
int Green(int color) { return (color >> 16) & 0xFF; }
int Blue(int color) { return (color >> 8) & 0xFF; }
int Alpha(int color) { return color & 0xFF; }

//色の差を任意の値で割り、割合も任意に決めて色を変える関数
int ChangeColor(int startColor, int aimColor, float divideNum, float rate) {

	//二色の差を求める
	int difRed = Red(aimColor) - Red(startColor);
	int difGreen = Green(aimColor) - Green(startColor);
	int difBlue = Blue(aimColor) - Blue(startColor);
	int difAlpha = Alpha(aimColor) - Alpha(startColor);

	//差分を任意の値で割る
	float dividedRed = float(difRed) / divideNum;
	float dividedGreen = float(difGreen) / divideNum;
	float dividedBlue = float(difBlue) / divideNum;
	float dividedAlpha = float(difAlpha) / divideNum;

	//割った値をrate倍する
	int Red = int(dividedRed * rate) << 24;
	int Green = int(dividedGreen * rate) << 16;
	int Blue = int(dividedBlue * rate) << 8;
	int Alpha = int(dividedAlpha * rate);

	//色を足して返す
	return startColor + Red + Green + Blue + Alpha;
}

//媒介変数tで色を変更する
int ChangeColorT(int startColor, int aimColor, float t) {

	//二色の差を求める
	int difRed = Red(aimColor) - Red(startColor);
	int difGreen = Green(aimColor) - Green(startColor);
	int difBlue = Blue(aimColor) - Blue(startColor);
	int difAlpha = Alpha(aimColor) - Alpha(startColor);

	int Red = int(difRed * t) << 24;
	int Green = int(difGreen * t) << 16;
	int Blue = int(difBlue * t) << 8;
	int Alpha = int(difAlpha * t);

	//色を足して返す
	return startColor + Red + Green + Blue + Alpha;
}

//グレースケールを求める関数
int GrayScale(int color) {

	int Red = (color >> 24) & 0xFF;
	int Green = (color >> 16) & 0xFF;
	int Blue = (color >> 8) & 0xFF;

	int trancedRed = int(float(Red) * 0.2126f);
	int trancedGreen = int(float(Green) * 0.7152f);
	int trancedBlue = int(float(Blue) * 0.0722f);

	int gray = int(trancedRed + trancedGreen + trancedBlue);

	return 0xFF + (gray << 24) + (gray << 16) + (gray << 8);
};

