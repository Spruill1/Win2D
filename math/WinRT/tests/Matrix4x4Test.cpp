//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

#include "pch.h"
#include "Helpers.h"

using namespace Microsoft::Graphics::Canvas::Math;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathTests
{
    TEST_CLASS(Matrix4x4Test)
    {
    public:
        static Matrix4x4 GenerateMatrixNumberFrom1To16()
        {
            Matrix4x4 a;
            a.M11 = 1.0f; a.M12 = 2.0f; a.M13 = 3.0f; a.M14 = 4.0f;
            a.M21 = 5.0f; a.M22 = 6.0f; a.M23 = 7.0f; a.M24 = 8.0f;
            a.M31 = 9.0f; a.M32 = 10.0f; a.M33 = 11.0f; a.M34 = 12.0f;
            a.M41 = 13.0f; a.M42 = 14.0f; a.M43 = 15.0f; a.M44 = 16.0f;
            return a;
        }

        static Matrix4x4 GenerateTestMatrix()
        {
            Matrix4x4 m =
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::CreateRotationX(ToRadians(30.0f)),
                        Matrix4x4Helper::CreateRotationY(ToRadians(30.0f))
                    ),
                    Matrix4x4Helper::CreateRotationZ(ToRadians(30.0f))
                );
            m.M41 = 111.0f;
            m.M42 = 222.0f;
            m.M43 = 333.0f;
            return m;
        }

        // A test for Matrix4x4 (float, float, float ... x16)
        TEST_METHOD(Matrix4x4ConstructorTest)
        {
            Matrix4x4 val = Matrix4x4Helper::FromValues(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

            Assert::AreEqual(val.M11, 1.0f);
            Assert::AreEqual(val.M12, 2.0f);
            Assert::AreEqual(val.M13, 3.0f);
            Assert::AreEqual(val.M14, 4.0f);
            Assert::AreEqual(val.M21, 5.0f);
            Assert::AreEqual(val.M22, 6.0f);
            Assert::AreEqual(val.M23, 7.0f);
            Assert::AreEqual(val.M24, 8.0f);
            Assert::AreEqual(val.M31, 9.0f);
            Assert::AreEqual(val.M32, 10.0f);
            Assert::AreEqual(val.M33, 11.0f);
            Assert::AreEqual(val.M34, 12.0f);
            Assert::AreEqual(val.M41, 13.0f);
            Assert::AreEqual(val.M42, 14.0f);
            Assert::AreEqual(val.M43, 15.0f);
            Assert::AreEqual(val.M44, 16.0f);
        }

        // A test for Identity
        TEST_METHOD(Matrix4x4IdentityTest)
        {
            Matrix4x4 val = Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

            Assert::IsTrue(Equal(val, Matrix4x4Helper::Identity), L"Matrix4x4Helper::Indentity was not set correctly.");
        }

        // A test for Determinant
        TEST_METHOD(Matrix4x4DeterminantTest)
        {
            Matrix4x4 target =
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::CreateRotationX(ToRadians(30.0f)),
                        Matrix4x4Helper::CreateRotationY(ToRadians(30.0f))
                    ),
                    Matrix4x4Helper::CreateRotationZ(ToRadians(30.0f))
                );
            float val = 1.0f;
            float det = Matrix4x4Helper::Determinant(target);

            Assert::IsTrue(Equal(val, det), L"Matrix4x4Helper::Determinant was not set correctly.");
        }

        // A test for Determinant
        TEST_METHOD(Matrix4x4DeterminantTest1)
        {
            Matrix4x4 a;
            a.M11 = 5.0f; a.M12 = 2.0f; a.M13 = 8.25f; a.M14 = 1.0f;
            a.M21 = 12.0f; a.M22 = 6.8f; a.M23 = 2.14f; a.M24 = 9.6f;
            a.M31 = 6.5f; a.M32 = 1.0f; a.M33 = 3.14f; a.M34 = 2.22f;
            a.M41 = 0.0f; a.M42 = 0.86f; a.M43 = 4.0f; a.M44 = 1.0f;
            Matrix4x4 i;
            Assert::IsTrue(Matrix4x4Helper::Invert(a, &i));

            float detA = Matrix4x4Helper::Determinant(a);
            float detI = Matrix4x4Helper::Determinant(i);
            float t = 1.0f / detI;

            // only accurate to 3 precision
            Assert::IsTrue(fabs(detA - t) < 1e-3, L"Matrix4x4Helper::Determinant was not set correctly.");
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertTest)
        {
            Matrix4x4 mtx =
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::CreateRotationX(ToRadians(30.0f)),
                        Matrix4x4Helper::CreateRotationY(ToRadians(30.0f))
                    ),
                    Matrix4x4Helper::CreateRotationZ(ToRadians(30.0f))
                );
            Matrix4x4 expected;
            expected.M11 = 0.74999994f;
            expected.M12 = -0.216506317f;
            expected.M13 = 0.62499994f;
            expected.M14 = 0.0f;

            expected.M21 = 0.433012635f;
            expected.M22 = 0.87499994f;
            expected.M23 = -0.216506317f;
            expected.M24 = 0.0f;

            expected.M31 = -0.49999997f;
            expected.M32 = 0.433012635f;
            expected.M33 = 0.74999994f;
            expected.M34 = 0.0f;

            expected.M41 = 0.0f;
            expected.M42 = 0.0f;
            expected.M43 = 0.0f;
            expected.M44 = 0.99999994f;

            Matrix4x4 actual;

            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::Invert did not return the expected value.");

            // Make sure M*M is identity matrix
            Matrix4x4 i = Matrix4x4Helper::Multiply(mtx, actual);
            Assert::IsTrue(Equal(i, Matrix4x4Helper::Identity), L"Matrix4x4Helper::Invert did not return the expected value.");
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertInPlaceTest)
        {
            Matrix4x4 mtx =
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::Multiply(
                            Matrix4x4Helper::Multiply(
                                Matrix4x4Helper::CreateRotationX(ToRadians(30.0f)),
                                Matrix4x4Helper::CreateRotationY(ToRadians(30.0f))
                            ),
                            Matrix4x4Helper::CreateRotationZ(ToRadians(30.0f))
                        ),
                        Matrix4x4Helper::CreateScale(3, 4, 5)
                    ),
                    Matrix4x4Helper::CreateTranslation(23, 42, 666)
                );

            Matrix4x4 expected;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &expected));

            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &mtx));
            Assert::IsTrue(Equal(expected, mtx), L"Matrix4x4Helper::Invert did not return the expected value.");
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertIdentityTest)
        {
            Matrix4x4 mtx = Matrix4x4Helper::Identity;

            Matrix4x4 actual;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));

            Assert::IsTrue(Equal(actual, Matrix4x4Helper::Identity));
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertTranslationTest)
        {
            Matrix4x4 mtx = Matrix4x4Helper::CreateTranslation(23, 42, 666);

            Matrix4x4 actual;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));

            Matrix4x4 i = Matrix4x4Helper::Multiply(mtx, actual);
            Assert::IsTrue(Equal(i, Matrix4x4Helper::Identity));
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertRotationTest)
        {
            Matrix4x4 mtx = Matrix4x4Helper::CreateFromYawPitchRoll(3, 4, 5);

            Matrix4x4 actual;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));

            Matrix4x4 i = Matrix4x4Helper::Multiply(mtx, actual);
            Assert::IsTrue(Equal(i, Matrix4x4Helper::Identity));
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertScaleTest)
        {
            Matrix4x4 mtx = Matrix4x4Helper::CreateScale(23, 42, -666);

            Matrix4x4 actual;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));

            Matrix4x4 i = Matrix4x4Helper::Multiply(mtx, actual);
            Assert::IsTrue(Equal(i, Matrix4x4Helper::Identity));
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertProjectionTest)
        {
            Matrix4x4 mtx = Matrix4x4Helper::CreatePerspectiveFieldOfView(1, 1.333f, 0.1f, 666);

            Matrix4x4 actual;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));

            Matrix4x4 i = Matrix4x4Helper::Multiply(mtx, actual);
            Assert::IsTrue(Equal(i, Matrix4x4Helper::Identity));
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertAffineTest)
        {
            Matrix4x4 mtx = 
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::CreateFromYawPitchRoll(3, 4, 5),
                        Matrix4x4Helper::CreateScale(23, 42, -666)
                    ),
                    Matrix4x4Helper::CreateTranslation(17, 53, 89)
                );

            Matrix4x4 actual;
            Assert::IsTrue(Matrix4x4Helper::Invert(mtx, &actual));

            Matrix4x4 i = Matrix4x4Helper::Multiply(mtx, actual);
            Assert::IsTrue(Equal(i, Matrix4x4Helper::Identity));
        }

        void DecomposeTest(float yaw, float pitch, float roll, Vector3 expectedTranslation, Vector3 expectedScales)
        {
            DecomposeTest(yaw, pitch, roll, expectedTranslation, expectedScales, true);
        }

        void DecomposeTest(float yaw, float pitch, float roll, Vector3 expectedTranslation, Vector3 expectedScales, bool expectedResult)
        {
            Quaternion expectedRotation = QuaternionHelper::CreateFromYawPitchRoll(
                ToRadians(yaw), ToRadians(pitch), ToRadians(roll));

            Matrix4x4 m = 
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::CreateScale(expectedScales.X, expectedScales.Y, expectedScales.Z),
                        Matrix4x4Helper::CreateFromQuaternion(expectedRotation)
                    ),
                    Matrix4x4Helper::CreateTranslation(expectedTranslation)
                );

            Vector3 scales;
            Quaternion rotation;
            Vector3 translation;

            bool actualResult = Matrix4x4Helper::Decompose(m, &scales, &rotation, &translation);
            Assert::AreEqual(expectedResult, actualResult, L"Matrix4x4Helper::Decompose did not return expected value.");
            if (expectedResult)
            {
                Assert::IsTrue(Equal(expectedScales, scales), L"Matrix4x4Helper::Decompose did not return expected value.");
            }
            else
            {
                Assert::IsTrue(Equal(fabs(expectedScales.X), fabs(scales.X)) &&
                               Equal(fabs(expectedScales.Y), fabs(scales.Y)) &&
                               Equal(fabs(expectedScales.Z), fabs(scales.Z)), L"Matrix4x4Helper::Decompose did not return expected value.");

            }
            Assert::IsTrue(EqualRotation(expectedRotation, rotation), L"Matrix4x4Helper::Decompose did not return expected value.");
            Assert::IsTrue(Equal(expectedTranslation, translation), L"Matrix4x4Helper::Decompose did not return expected value.");
        }
        
        TEST_METHOD(Matrix4x4DecomposeTest01)
        {
            DecomposeTest(10.0f, 20.0f, 30.0f, Vector3Helper::FromValues(10, 20, 30), Vector3Helper::FromValues(2, 3, 4));

            const float step = 234.0f;

            for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
            {
                for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
                {
                    for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
                    {
                        DecomposeTest(yawAngle, pitchAngle, rollAngle, Vector3Helper::FromValues(10, 20, 30), Vector3Helper::FromValues(2, 3, 4));
                    }
                }
            }
        }
        
        TEST_METHOD(Matrix4x4DecomposeTest02)
        {
            DecomposeTest(10.0f, 20.0f, 30.0f, Vector3Helper::FromValues(10, 20, 30), Vector3Helper::FromValues(2, 3, 4));

            // Various scales.
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(1, 2, 3));
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(1, 3, 2));
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(2, 1, 3));
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(2, 3, 1));
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(3, 1, 2));
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(3, 2, 1));

            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(-2, 1, 1));

            // Small scales.
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(1e-6f, 2e-6f, 3e-6f), false);
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(1e-6f, 3e-6f, 2e-6f), false);
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(2e-6f, 1e-6f, 3e-6f), false);
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(2e-6f, 3e-6f, 1e-6f), false);
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(3e-6f, 1e-6f, 2e-6f), false);
            DecomposeTest(0, 0, 0, Vector3Helper::Zero, Vector3Helper::FromValues(3e-6f, 2e-6f, 1e-6f), false);
        }

        void DecomposeScaleTest(float sx, float sy, float sz)
        {
            Matrix4x4 m = Matrix4x4Helper::CreateScale(1, 2e-6f, 1e-6f);
            m.M11 = sx;
            m.M12 = sy;
            m.M13 = sz;

            Vector3 expectedScales = Vector3Helper::FromValues(1, 2e-6f, 1e-6f);
            Vector3 scales;
            Quaternion rotation;
            Vector3 translation;

            bool actualResult = Matrix4x4Helper::Decompose(m, &scales, &rotation, &translation);
            Assert::AreEqual(false, actualResult, L"Matrix4x4Helper::Decompose did not return expected value.");
            Assert::IsTrue(Equal(fabs(expectedScales.X), fabs(scales.X)) &&
                           Equal(fabs(expectedScales.Y), fabs(scales.Y)) &&
                           Equal(fabs(expectedScales.Z), fabs(scales.Z)), L"Matrix4x4Helper::Decompose did not return expected value.");

            Assert::IsTrue(EqualRotation(QuaternionHelper::Identity, rotation), L"Matrix4x4Helper::Decompose did not return expected value.");
            Assert::IsTrue(Equal(Vector3Helper::Zero, translation), L"Matrix4x4Helper::Decompose did not return expected value.");
        }

        TEST_METHOD(Matrix4x4DecomposeTest03)
        {
            DecomposeScaleTest(1, 2e-6f, 3e-6f);
            DecomposeScaleTest(1, 3e-6f, 2e-6f);
            DecomposeScaleTest(2e-6f, 1, 3e-6f);
            DecomposeScaleTest(2e-6f, 3e-6f, 1);
            DecomposeScaleTest(3e-6f, 1, 2e-6f);
            DecomposeScaleTest(3e-6f, 2e-6f, 1);
        }

        TEST_METHOD(Matrix4x4TransformTest)
        {
            Matrix4x4 target = GenerateMatrixNumberFrom1To16();

            Matrix4x4 m =
                Matrix4x4Helper::Multiply(
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::CreateRotationX(ToRadians(30.0f)),
                        Matrix4x4Helper::CreateRotationY(ToRadians(30.0f))
                    ),
                    Matrix4x4Helper::CreateRotationZ(ToRadians(30.0f))
                );
            Quaternion q = QuaternionHelper::CreateFromRotationMatrix(m);

            Matrix4x4 expected = Matrix4x4Helper::Multiply(target, m);
            Matrix4x4 actual;
            actual = Matrix4x4Helper::Transform(target, q);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::Transform did not return the expected value.");
        }

        // A test for CreateRotationX (float)
        TEST_METHOD(Matrix4x4CreateRotationXTest)
        {
            float radians = ToRadians(30.0f);

            Matrix4x4 expected = Matrix4x4Helper::Identity;

            expected.M11 = 1.0f;
            expected.M22 = 0.8660254f;
            expected.M23 = 0.5f;
            expected.M32 = -0.5f;
            expected.M33 = 0.8660254f;

            Matrix4x4 actual;

            actual = Matrix4x4Helper::CreateRotationX(radians);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateRotationX did not return the expected value.");
        }

        // A test for CreateRotationX (float)
        TEST_METHOD(Matrix4x4CreateRotationXTest1)
        {
            float radians = 0;

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            Matrix4x4 actual = Matrix4x4Helper::CreateRotationX(radians);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateRotationX did not return the expected value.");
        }

        // A test for CreateRotationX (float, Vector3)
        TEST_METHOD(Matrix4x4CreateRotationXCenterTest)
        {
            float radians = ToRadians(30.0f);
            Vector3 center = Vector3Helper::FromValues(23, 42, 66);

            Matrix4x4 rotateAroundZero = Matrix4x4Helper::CreateRotationX(radians, Vector3Helper::Zero);
            Matrix4x4 rotateAroundZeroExpected = Matrix4x4Helper::CreateRotationX(radians);
            Assert::IsTrue(Equal(rotateAroundZero, rotateAroundZeroExpected));

            Matrix4x4 rotateAroundCenter = Matrix4x4Helper::CreateRotationX(radians, center);
            Matrix4x4 rotateAroundCenterExpected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateTranslation(Vector3Helper::Negate(center)), Matrix4x4Helper::CreateRotationX(radians)), Matrix4x4Helper::CreateTranslation(center));
            Assert::IsTrue(Equal(rotateAroundCenter, rotateAroundCenterExpected));
        }

        // A test for CreateRotationY (float)
        TEST_METHOD(Matrix4x4CreateRotationYTest)
        {
            float radians = ToRadians(60.0f);

            Matrix4x4 expected = Matrix4x4Helper::Identity;

            expected.M11 = 0.49999997f;
            expected.M13 = -0.866025448f;
            expected.M22 = 1.0f;
            expected.M31 = 0.866025448f;
            expected.M33 = 0.49999997f;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::CreateRotationY(radians);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateRotationY did not return the expected value.");
        }

        // A test for RotationY (float)
        TEST_METHOD(Matrix4x4CreateRotationYTest1)
        {
            float radians = ToRadians(-300.0f);

            Matrix4x4 expected = Matrix4x4Helper::Identity;

            expected.M11 = 0.49999997f;
            expected.M13 = -0.866025448f;
            expected.M22 = 1.0f;
            expected.M31 = 0.866025448f;
            expected.M33 = 0.49999997f;

            Matrix4x4 actual = Matrix4x4Helper::CreateRotationY(radians);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateRotationY did not return the expected value.");
        }

        // A test for CreateRotationY (float, Vector3)
        TEST_METHOD(Matrix4x4CreateRotationYCenterTest)
        {
            float radians = ToRadians(30.0f);
            Vector3 center = Vector3Helper::FromValues(23, 42, 66);

            Matrix4x4 rotateAroundZero = Matrix4x4Helper::CreateRotationY(radians, Vector3Helper::Zero);
            Matrix4x4 rotateAroundZeroExpected = Matrix4x4Helper::CreateRotationY(radians);
            Assert::IsTrue(Equal(rotateAroundZero, rotateAroundZeroExpected));

            Matrix4x4 rotateAroundCenter = Matrix4x4Helper::CreateRotationY(radians, center);
            Matrix4x4 rotateAroundCenterExpected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateTranslation(Vector3Helper::Negate(center)), Matrix4x4Helper::CreateRotationY(radians)), Matrix4x4Helper::CreateTranslation(center));
            Assert::IsTrue(Equal(rotateAroundCenter, rotateAroundCenterExpected));
        }

        // A test for CreateFromAxisAngle(Vector3,float)
        TEST_METHOD(Matrix4x4CreateFromAxisAngleTest)
        {
            float radians = ToRadians(-30.0f);

            Matrix4x4 expected = Matrix4x4Helper::CreateRotationX(radians);
            Matrix4x4 actual = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitX, radians);
            Assert::IsTrue(Equal(expected, actual));

            expected = Matrix4x4Helper::CreateRotationY(radians);
            actual = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitY, radians);
            Assert::IsTrue(Equal(expected, actual));

            expected = Matrix4x4Helper::CreateRotationZ(radians);
            actual = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitZ, radians);
            Assert::IsTrue(Equal(expected, actual));

            expected = Matrix4x4Helper::CreateFromQuaternion(QuaternionHelper::CreateFromAxisAngle(Vector3Helper::Normalize(Vector3Helper::One), radians));
            actual = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::Normalize(Vector3Helper::One), radians);
            Assert::IsTrue(Equal(expected, actual));

            const int rotCount = 8;
            for (int i = 0; i < rotCount; ++i)
            {
                float latitude = (2.0f * DirectX::XM_PI) * ((float)i / (float)rotCount);
                for (int j = 0; j < rotCount; ++j)
                {
                    float longitude = -DirectX::XM_PIDIV2 + DirectX::XM_PI * ((float)j / (float)rotCount);

                    Matrix4x4 m = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(longitude), Matrix4x4Helper::CreateRotationY(latitude));
                    Vector3 axis = Vector3Helper::FromValues(m.M11, m.M12, m.M13);
                    for (int k = 0; k < rotCount; ++k)
                    {
                        float rot = (2.0f * DirectX::XM_PI) * ((float)k / (float)rotCount);
                        expected = Matrix4x4Helper::CreateFromQuaternion(QuaternionHelper::CreateFromAxisAngle(axis, rot));
                        actual = Matrix4x4Helper::CreateFromAxisAngle(axis, rot);
                        Assert::IsTrue(Equal(expected, actual));
                    }
                }
            }
        }
        
        TEST_METHOD(Matrix4x4CreateFromYawPitchRollTest1)
        {
            float yawAngle = ToRadians(30.0f);
            float pitchAngle = ToRadians(40.0f);
            float rollAngle = ToRadians(50.0f);

            Matrix4x4 yaw = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitY, yawAngle);
            Matrix4x4 pitch = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitX, pitchAngle);
            Matrix4x4 roll = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitZ, rollAngle);

            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(roll, pitch), yaw);
            Matrix4x4 actual = Matrix4x4Helper::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);
            Assert::IsTrue(Equal(expected, actual));
        }
        
        TEST_METHOD(Matrix4x4CreateFromYawPitchRollTest2)
        {
            const float step = 234;

            for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
            {
                for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
                {
                    for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
                    {
                        float yawRad = ToRadians(yawAngle);
                        float pitchRad = ToRadians(pitchAngle);
                        float rollRad = ToRadians(rollAngle);
                        Matrix4x4 yaw = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitY, yawRad);
                        Matrix4x4 pitch = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitX, pitchRad);
                        Matrix4x4 roll = Matrix4x4Helper::CreateFromAxisAngle(Vector3Helper::UnitZ, rollRad);

                        Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(roll, pitch), yaw);
                        Matrix4x4 actual = Matrix4x4Helper::CreateFromYawPitchRoll(yawRad, pitchRad, rollRad);
                        Assert::IsTrue(Equal(expected, actual));
                    }
                }
            }
        }

        TEST_METHOD(Matrix4x4CreateShadowTest01)
        {
            Vector3 lightDir = Vector3Helper::UnitY;
            Plane plane = PlaneHelper::FromVector3(Vector3Helper::UnitY, 0);

            Matrix4x4 expected = Matrix4x4Helper::CreateScale(1, 0, 1);

            Matrix4x4 actual = Matrix4x4Helper::CreateShadow(lightDir, plane);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateShadow did not returned expected value.");
        }
        
        TEST_METHOD(Matrix4x4CreateShadowTest02)
        {
            // Complex cases.
            Plane planes[] =
            {
                PlaneHelper::FromValues( 0, 1, 0, 0 ),
                PlaneHelper::FromValues(1, 2, 3, 4),
                PlaneHelper::FromValues(5, 6, 7, 8),
                PlaneHelper::FromValues(-1, -2, -3, -4),
                PlaneHelper::FromValues(-5, -6, -7, -8),
            };

            Vector3 points[] =
            {
                Vector3Helper::FromValues( 1, 2, 3),
                Vector3Helper::FromValues(5, 6, 7),
                Vector3Helper::FromValues(8, 9, 10),
                Vector3Helper::FromValues(-1, -2, -3),
                Vector3Helper::FromValues(-5, -6, -7),
                Vector3Helper::FromValues(-8, -9, -10),
            };

            for (int i = 0; i < sizeof(planes) / sizeof(planes[0]); i++)
            {
                Plane plane = PlaneHelper::Normalize(planes[i]);

                // Try various direction of light directions.
                Vector3 testDirections[]
                {
                    Vector3Helper::FromValues( -1.0f,  1.0f, 1.0f ),
                    Vector3Helper::FromValues(  0.0f,  1.0f, 1.0f ),
                    Vector3Helper::FromValues(  1.0f,  1.0f, 1.0f ),
                    Vector3Helper::FromValues( -1.0f,  0.0f, 1.0f ),
                    Vector3Helper::FromValues(  0.0f,  0.0f, 1.0f ),
                    Vector3Helper::FromValues(  1.0f,  0.0f, 1.0f ),
                    Vector3Helper::FromValues( -1.0f, -1.0f, 1.0f ),
                    Vector3Helper::FromValues(  0.0f, -1.0f, 1.0f ),
                    Vector3Helper::FromValues(  1.0f, -1.0f, 1.0f ),

                    Vector3Helper::FromValues( -1.0f, 1.0f, 0.0f ),
                    Vector3Helper::FromValues(  0.0f, 1.0f, 0.0f ),
                    Vector3Helper::FromValues(  1.0f, 1.0f, 0.0f ),
                    Vector3Helper::FromValues( -1.0f, 0.0f, 0.0f ),
                    Vector3Helper::FromValues(  0.0f, 0.0f, 0.0f ),
                    Vector3Helper::FromValues(  1.0f, 0.0f, 0.0f ),
                    Vector3Helper::FromValues( -1.0f,-1.0f, 0.0f ),
                    Vector3Helper::FromValues(  0.0f,-1.0f, 0.0f ),
                    Vector3Helper::FromValues(  1.0f,-1.0f, 0.0f ),

                    Vector3Helper::FromValues( -1.0f, 1.0f,-1.0f ),
                    Vector3Helper::FromValues(  0.0f, 1.0f,-1.0f ),
                    Vector3Helper::FromValues(  1.0f, 1.0f,-1.0f ),
                    Vector3Helper::FromValues( -1.0f, 0.0f,-1.0f ),
                    Vector3Helper::FromValues(  0.0f, 0.0f,-1.0f ),
                    Vector3Helper::FromValues(  1.0f, 0.0f,-1.0f ),
                    Vector3Helper::FromValues( -1.0f,-1.0f,-1.0f ),
                    Vector3Helper::FromValues(  0.0f,-1.0f,-1.0f ),
                    Vector3Helper::FromValues(  1.0f,-1.0f,-1.0f ),
                };

                for (int j = 0; j < sizeof(testDirections) / sizeof(testDirections[0]); j++)
                {
                    Vector3 lightDirInfo = testDirections[j];

                    if (Vector3Helper::Length(lightDirInfo) < 0.1f) continue;
                    Vector3 lightDir = Vector3Helper::Normalize(lightDirInfo);

                    if (PlaneHelper::DotNormal(plane, lightDir) < 0.1f) continue;

                    Matrix4x4 m = Matrix4x4Helper::CreateShadow(lightDir, plane);
                    Vector3 pp = Vector3Helper::MultiplyByScalar(plane.Normal, -plane.D); // origin of the plane.

                    for (int k = 0; k < sizeof(points) / sizeof(points[0]); k++)
                    {
                        Vector3 point = points[k];

                        Vector4 v4 = Vector4Helper::TransformVector3(point, m);

                        Vector3 sp = Vector3Helper::DivideByScalar(Vector3Helper::FromValues(v4.X, v4.Y, v4.Z), v4.W);

                        // Make sure transformed position is on the plane.
                        Vector3 v = Vector3Helper::Subtract(sp, pp);
                        float d = Vector3Helper::Dot(v, plane.Normal);
                        Assert::IsTrue(Equal(d, 0), L"Matrix4x4Helper::CreateShadow did not provide expected value.");

                        // make sure direction between transformed position and original position are same as light direction.
                        if (Vector3Helper::Dot(Vector3Helper::Subtract(point, pp), plane.Normal) > 0.0001f)
                        {
                            Vector3 dir = Vector3Helper::Normalize(Vector3Helper::Subtract(point, sp));
                            Assert::IsTrue(Equal(dir, lightDir), L"Matrix4x4Helper::CreateShadow did not provide expected value.");
                        }
                    }
                }
            }
        }

        void CreateReflectionTest(Plane plane, Matrix4x4 expected)
        {
            Matrix4x4 actual = Matrix4x4Helper::CreateReflection(plane);
            Assert::IsTrue(Equal(actual, expected), L"Matrix4x4Helper::CreateReflection did not return expected value.");
        }

        TEST_METHOD(Matrix4x4CreateReflectionTest01)
        {
            // XY plane.
            CreateReflectionTest(PlaneHelper::FromVector3(Vector3Helper::UnitZ, 0), Matrix4x4Helper::CreateScale(1, 1, -1));
            // XZ plane.
            CreateReflectionTest(PlaneHelper::FromVector3(Vector3Helper::UnitY, 0), Matrix4x4Helper::CreateScale(1, -1, 1));
            // YZ plane.
            CreateReflectionTest(PlaneHelper::FromVector3(Vector3Helper::UnitX, 0), Matrix4x4Helper::CreateScale(-1, 1, 1));

            // Complex cases.
            Plane planes[] =
            {
                PlaneHelper::FromValues( 0, 1, 0, 0 ),
                PlaneHelper::FromValues( 1, 2, 3, 4 ),
                PlaneHelper::FromValues( 5, 6, 7, 8 ),
                PlaneHelper::FromValues(-1,-2,-3,-4 ),
                PlaneHelper::FromValues(-5,-6,-7,-8 ),
            };

            Vector3 points[] =
            {
                Vector3Helper::FromValues( 1, 2, 3),
                Vector3Helper::FromValues( 5, 6, 7),
                Vector3Helper::FromValues(-1,-2,-3),
                Vector3Helper::FromValues(-5,-6,-7),
            };

            for (int i = 0; i < sizeof(planes) / sizeof(planes[0]); i++)
            {
                Plane plane = PlaneHelper::Normalize(planes[i]);
                Matrix4x4 m = Matrix4x4Helper::CreateReflection(plane);
                Vector3 pp = Vector3Helper::MultiplyByScalar(plane.Normal, -plane.D); // Position on the plane.

                for (int j = 0; j < sizeof(points) / sizeof(points[0]); j++)
                {
                    Vector3 point = points[j];

                    Vector3 rp = Vector3Helper::Transform(point, m);

                    // Maniually compute refelction point and compare results.
                    Vector3 v = Vector3Helper::Subtract(point, pp);
                    float d = Vector3Helper::Dot(v, plane.Normal);
                    Vector3 vp = Vector3Helper::Subtract(point, Vector3Helper::MultiplyByScalar(plane.Normal, 2.0f * d));
                    Assert::IsTrue(Equal(rp, vp), L"Matrix4x4Helper::Reflection did not provide expected value.");
                }
            }
        }

        // A test for CreateRotationZ (float)
        TEST_METHOD(Matrix4x4CreateRotationZTest)
        {
            float radians = ToRadians(50.0f);

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 0.642787635f;
            expected.M12 = 0.766044438f;
            expected.M21 = -0.766044438f;
            expected.M22 = 0.642787635f;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::CreateRotationZ(radians);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateRotationZ did not return the expected value.");
        }

        // A test for CreateRotationZ (float, Vector3)
        TEST_METHOD(Matrix4x4CreateRotationZCenterTest)
        {
            float radians = ToRadians(30.0f);
            Vector3 center = Vector3Helper::FromValues(23, 42, 66);

            Matrix4x4 rotateAroundZero = Matrix4x4Helper::CreateRotationZ(radians, Vector3Helper::Zero);
            Matrix4x4 rotateAroundZeroExpected = Matrix4x4Helper::CreateRotationZ(radians);
            Assert::IsTrue(Equal(rotateAroundZero, rotateAroundZeroExpected));

            Matrix4x4 rotateAroundCenter = Matrix4x4Helper::CreateRotationZ(radians, center);
            Matrix4x4 rotateAroundCenterExpected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateTranslation(Vector3Helper::Negate(center)), Matrix4x4Helper::CreateRotationZ(radians)), Matrix4x4Helper::CreateTranslation(center));
            Assert::IsTrue(Equal(rotateAroundCenter, rotateAroundCenterExpected));
        }

        // A test for CreateLookAt (Vector3, Vector3, Vector3)
        TEST_METHOD(Matrix4x4CreateLookAtTest)
        {
            Vector3 cameraPosition = Vector3Helper::FromValues(10.0f, 20.0f, 30.0f);
            Vector3 cameraTarget = Vector3Helper::FromValues(3.0f, 2.0f, -4.0f);
            Vector3 cameraUpVector = Vector3Helper::FromValues(0.0f, 1.0f, 0.0f);

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 0.979457f;
            expected.M12 = -0.0928267762f;
            expected.M13 = 0.179017f;

            expected.M21 = 0.0f;
            expected.M22 = 0.8877481f;
            expected.M23 = 0.460329473f;

            expected.M31 = -0.201652914f;
            expected.M32 = -0.450872928f;
            expected.M33 = 0.8695112f;

            expected.M41 = -3.74498272f;
            expected.M42 = -3.30050683f;
            expected.M43 = -37.0820961f;

            Matrix4x4 actual = Matrix4x4Helper::CreateLookAt(cameraPosition, cameraTarget, cameraUpVector);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateLookAt did not return the expected value.");
        }

        // A test for CreateWorld (Vector3, Vector3, Vector3)
        TEST_METHOD(Matrix4x4CreateWorldTest)
        {
            Vector3 objectPosition = Vector3Helper::FromValues(10.0f, 20.0f, 30.0f);
            Vector3 objectForwardDirection = Vector3Helper::FromValues(3.0f, 2.0f, -4.0f);
            Vector3 objectUpVector = Vector3Helper::FromValues(0.0f, 1.0f, 0.0f);

            Matrix4x4 expected;
            expected.M11 = 0.799999952f;
            expected.M12 = 0;
            expected.M13 = 0.599999964f;
            expected.M14 = 0;

            expected.M21 = -0.2228344f;
            expected.M22 = 0.928476632f;
            expected.M23 = 0.297112525f;
            expected.M24 = 0;

            expected.M31 = -0.557086f;
            expected.M32 = -0.371390671f;
            expected.M33 = 0.742781341f;
            expected.M34 = 0;

            expected.M41 = 10;
            expected.M42 = 20;
            expected.M43 = 30;
            expected.M44 = 1.0f;

            Matrix4x4 actual = Matrix4x4Helper::CreateWorld(objectPosition, objectForwardDirection, objectUpVector);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateWorld did not return the expected value.");

            Assert::AreEqual(objectPosition, Matrix4x4Helper::Translation(actual));
            Assert::IsTrue(Vector3Helper::Dot(Vector3Helper::Normalize(objectUpVector), Vector3Helper::FromValues(actual.M21, actual.M22, actual.M23)) > 0);
            Assert::IsTrue(Vector3Helper::Dot(Vector3Helper::Normalize(objectForwardDirection), Vector3Helper::FromValues(-actual.M31, -actual.M32, -actual.M33)) > 0.999f);
        }

        // A test for CreateOrtho (float, float, float, float)
        TEST_METHOD(Matrix4x4CreateOrthoTest)
        {
            float width = 100.0f;
            float height = 200.0f;
            float zNearPlane = 1.5f;
            float zFarPlane = 1000.0f;

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 0.02f;
            expected.M22 = 0.01f;
            expected.M33 = -0.00100150227f;
            expected.M43 = -0.00150225335f;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::CreateOrthographic(width, height, zNearPlane, zFarPlane);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateOrtho did not return the expected value.");
        }

        // A test for CreateOrthoOffCenter (float, float, float, float, float, float)
        TEST_METHOD(Matrix4x4CreateOrthoOffCenterTest)
        {
            float left = 10.0f;
            float right = 90.0f;
            float bottom = 20.0f;
            float top = 180.0f;
            float zNearPlane = 1.5f;
            float zFarPlane = 1000.0f;

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 0.025f;
            expected.M22 = 0.0125f;
            expected.M33 = -0.00100150227f;
            expected.M41 = -1.25f;
            expected.M42 = -1.25f;
            expected.M43 = -0.00150225335f;
            expected.M44 = 1.0f;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateOrthoOffCenter did not return the expected value.");
        }

        // A test for CreatePerspective (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveTest)
        {
            float width = 100.0f;
            float height = 200.0f;
            float zNearPlane = 1.5f;
            float zFarPlane = 1000.0f;

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 0.03f;
            expected.M22 = 0.015f;
            expected.M33 = -1.00150228f;
            expected.M34 = -1.0f;
            expected.M43 = -1.50225341f;
            expected.M44 = 0;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::CreatePerspective(width, height, zNearPlane, zFarPlane);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreatePerspective did not return the expected value.");
        }

        // A test for CreatePerspective (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveTest1)
        {
            try
            {
                float width = 100.0f;
                float height = 200.0f;
                float zNearPlane = 0.0f;
                float zFarPlane = 0.0f;

                Matrix4x4 actual = Matrix4x4Helper::CreatePerspective(width, height, zNearPlane, zFarPlane);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspective (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveTest2)
        {
            try
            {
                Matrix4x4 actual = Matrix4x4Helper::CreatePerspective(10, 10, -10, 10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspective (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveTest3)
        {
            try
            {
                Matrix4x4 actual = Matrix4x4Helper::CreatePerspective(10, 10, 10, -10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspective (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveTest4)
        {
            try
            {
                Matrix4x4 actual = Matrix4x4Helper::CreatePerspective(10, 10, 10, 1);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveFieldOfView (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveFieldOfViewTest)
        {
            float fieldOfView = ToRadians(30.0f);
            float aspectRatio = 1280.0f / 720.0f;
            float zNearPlane = 1.5f;
            float zFarPlane = 1000.0f;

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 2.09927845f;
            expected.M22 = 3.73205066f;
            expected.M33 = -1.00150228f;
            expected.M34 = -1.0f;
            expected.M43 = -1.50225341f;
            expected.M44 = 0;
            Matrix4x4 actual;

            actual = Matrix4x4Helper::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, zNearPlane, zFarPlane);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreatePerspectiveFieldOfView did not return the expected value.");
        }

        // A test for CreatePerspectiveFieldOfView (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveFieldOfViewTest1)
        {
            try
            {
                Matrix4x4 mtx = Matrix4x4Helper::CreatePerspectiveFieldOfView(-1, 1, 1, 10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveFieldOfView (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveFieldOfViewTest2)
        {
            try
            {
                Matrix4x4 mtx = Matrix4x4Helper::CreatePerspectiveFieldOfView(DirectX::XM_PI + 0.01f, 1, 1, 10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveFieldOfView (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveFieldOfViewTest3)
        {
            try
            {
                Matrix4x4 mtx = Matrix4x4Helper::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, 1, -1, 10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveFieldOfView (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveFieldOfViewTest4)
        {
            try
            {
                Matrix4x4 mtx = Matrix4x4Helper::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, 1, 1, -10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveFieldOfView (float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveFieldOfViewTest5)
        {
            try
            {
                Matrix4x4 mtx = Matrix4x4Helper::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, 1, 10, 1);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveOffCenterTest)
        {
            float left = 10.0f;
            float right = 90.0f;
            float bottom = 20.0f;
            float top = 180.0f;
            float zNearPlane = 1.5f;
            float zFarPlane = 1000.0f;

            Matrix4x4 expected = Matrix4x4Helper::Identity;
            expected.M11 = 0.0375f;
            expected.M22 = 0.01875f;
            expected.M31 = 1.25f;
            expected.M32 = 1.25f;
            expected.M33 = -1.00150228f;
            expected.M34 = -1.0f;
            expected.M43 = -1.50225341f;
            expected.M44 = 0;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::CreatePerspectiveOffCenter(left, right, bottom, top, zNearPlane, zFarPlane);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreatePerspectiveOffCenter did not return the expected value.");
        }

        // A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveOffCenterTest1)
        {
            try
            {
                float left = 10.0f, right = 90.0f, bottom = 20.0f, top = 180.0f;
                Matrix4x4 actual = Matrix4x4Helper::CreatePerspectiveOffCenter(left, right, bottom, top, -1, 10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveOffCenterTest2)
        {
            try
            {
                float left = 10.0f, right = 90.0f, bottom = 20.0f, top = 180.0f;
                Matrix4x4 actual = Matrix4x4Helper::CreatePerspectiveOffCenter(left, right, bottom, top, 1, -10);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)
        TEST_METHOD(Matrix4x4CreatePerspectiveOffCenterTest3)
        {
            try
            {
                float left = 10.0f, right = 90.0f, bottom = 20.0f, top = 180.0f;
                Matrix4x4 actual = Matrix4x4Helper::CreatePerspectiveOffCenter(left, right, bottom, top, 10, 1);

                Assert::Fail(L"should have thrown");
            }
            catch (Platform::InvalidArgumentException^)
            {
            }
        }

        // A test for Invert (Matrix4x4)
        TEST_METHOD(Matrix4x4InvertTest1)
        {
            Matrix4x4 a;
            a.M11 = 1.0f; a.M12 = 2.0f; a.M13 = 3.0f; a.M14 = 4.0f;
            a.M21 = 5.0f; a.M22 = 6.0f; a.M23 = 7.0f; a.M24 = 8.0f;
            a.M31 = 9.0f; a.M32 = 10.0f; a.M33 = 11.0f; a.M34 = 12.0f;
            a.M41 = 13.0f; a.M42 = 14.0f; a.M43 = 15.0f; a.M44 = 16.0f;

            float detA = Matrix4x4Helper::Determinant(a);
            Assert::IsTrue(Equal(detA, 0.0f), L"Matrix4x4Helper::Invert did not return the expected value.");

            Matrix4x4 actual;
            Assert::IsFalse(Matrix4x4Helper::Invert(a, &actual));

            // all the elements in Actual is NaN
            Assert::IsTrue(
                isnan(actual.M11) && isnan(actual.M12) && isnan(actual.M13) && isnan(actual.M14) &&
                isnan(actual.M21) && isnan(actual.M22) && isnan(actual.M23) && isnan(actual.M24) &&
                isnan(actual.M31) && isnan(actual.M32) && isnan(actual.M33) && isnan(actual.M34) &&
                isnan(actual.M41) && isnan(actual.M42) && isnan(actual.M43) && isnan(actual.M44)
                , L"Matrix4x4Helper::Invert did not return the expected value.");
        }

        // A test for Lerp (Matrix4x4, Matrix4x4, float)
        TEST_METHOD(Matrix4x4LerpTest)
        {
            Matrix4x4 a;
            a.M11 = 11.0f; a.M12 = 12.0f; a.M13 = 13.0f; a.M14 = 14.0f;
            a.M21 = 21.0f; a.M22 = 22.0f; a.M23 = 23.0f; a.M24 = 24.0f;
            a.M31 = 31.0f; a.M32 = 32.0f; a.M33 = 33.0f; a.M34 = 34.0f;
            a.M41 = 41.0f; a.M42 = 42.0f; a.M43 = 43.0f; a.M44 = 44.0f;

            Matrix4x4 b = GenerateMatrixNumberFrom1To16();

            float t = 0.5f;

            Matrix4x4 expected;
            expected.M11 = a.M11 + (b.M11 - a.M11) * t;
            expected.M12 = a.M12 + (b.M12 - a.M12) * t;
            expected.M13 = a.M13 + (b.M13 - a.M13) * t;
            expected.M14 = a.M14 + (b.M14 - a.M14) * t;

            expected.M21 = a.M21 + (b.M21 - a.M21) * t;
            expected.M22 = a.M22 + (b.M22 - a.M22) * t;
            expected.M23 = a.M23 + (b.M23 - a.M23) * t;
            expected.M24 = a.M24 + (b.M24 - a.M24) * t;

            expected.M31 = a.M31 + (b.M31 - a.M31) * t;
            expected.M32 = a.M32 + (b.M32 - a.M32) * t;
            expected.M33 = a.M33 + (b.M33 - a.M33) * t;
            expected.M34 = a.M34 + (b.M34 - a.M34) * t;

            expected.M41 = a.M41 + (b.M41 - a.M41) * t;
            expected.M42 = a.M42 + (b.M42 - a.M42) * t;
            expected.M43 = a.M43 + (b.M43 - a.M43) * t;
            expected.M44 = a.M44 + (b.M44 - a.M44) * t;

            Matrix4x4 actual;
            actual = Matrix4x4Helper::Lerp(a, b, t);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::Lerp did not return the expected value.");
        }

        // A test for Transpose (Matrix4x4)
        TEST_METHOD(Matrix4x4TransposeTest)
        {
            Matrix4x4 a = GenerateMatrixNumberFrom1To16();

            Matrix4x4 expected;
            expected.M11 = a.M11; expected.M12 = a.M21; expected.M13 = a.M31; expected.M14 = a.M41;
            expected.M21 = a.M12; expected.M22 = a.M22; expected.M23 = a.M32; expected.M24 = a.M42;
            expected.M31 = a.M13; expected.M32 = a.M23; expected.M33 = a.M33; expected.M34 = a.M43;
            expected.M41 = a.M14; expected.M42 = a.M24; expected.M43 = a.M34; expected.M44 = a.M44;

            Matrix4x4 actual = Matrix4x4Helper::Transpose(a);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::Transpose did not return the expected value.");
        }

        // A test for Transpose (Matrix4x4)
        TEST_METHOD(Matrix4x4TransposeTest1)
        {
            Matrix4x4 a = Matrix4x4Helper::Identity;
            Matrix4x4 expected = Matrix4x4Helper::Identity;

            Matrix4x4 actual = Matrix4x4Helper::Transpose(a);
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::Transpose did not return the expected value.");
        }

        // A test for Matrix4x4 (Quaternion)
        TEST_METHOD(Matrix4x4FromQuaternionTest1)
        {
            Vector3 axis = Vector3Helper::Normalize(Vector3Helper::FromValues(1.0f, 2.0f, 3.0f));
            Quaternion q = QuaternionHelper::CreateFromAxisAngle(axis, ToRadians(30.0f));

            Matrix4x4 expected;
            expected.M11 = 0.875595033f;
            expected.M12 = 0.420031041f;
            expected.M13 = -0.2385524f;
            expected.M14 = 0.0f;

            expected.M21 = -0.38175258f;
            expected.M22 = 0.904303849f;
            expected.M23 = 0.1910483f;
            expected.M24 = 0.0f;

            expected.M31 = 0.295970082f;
            expected.M32 = -0.07621294f;
            expected.M33 = 0.952151954f;
            expected.M34 = 0.0f;

            expected.M41 = 0.0f;
            expected.M42 = 0.0f;
            expected.M43 = 0.0f;
            expected.M44 = 1.0f;

            Matrix4x4 target = Matrix4x4Helper::CreateFromQuaternion(q);
            Assert::IsTrue(Equal(expected, target), L"Matrix4x4Helper::Matrix4x4(Quaternion) did not return the expected value.");
        }

        // A test for FromQuaternion (Matrix4x4)
        TEST_METHOD(Matrix4x4FromQuaternionTest2)
        {
            for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
            {
                Quaternion quat = QuaternionHelper::CreateFromAxisAngle(Vector3Helper::UnitX, angle);

                Matrix4x4 expected = Matrix4x4Helper::CreateRotationX(angle);
                Matrix4x4 actual = Matrix4x4Helper::CreateFromQuaternion(quat);
                Assert::IsTrue(Equal(expected, actual),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");

                // make sure convert back to quaternion is same as we passed QuaternionHelper::
                Quaternion q2 = QuaternionHelper::CreateFromRotationMatrix(actual);
                Assert::IsTrue(EqualRotation(quat, q2),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");
            }
        }

        // A test for FromQuaternion (Matrix4x4)
        TEST_METHOD(Matrix4x4FromQuaternionTest3)
        {
            for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
            {
                Quaternion quat = QuaternionHelper::CreateFromAxisAngle(Vector3Helper::UnitY, angle);

                Matrix4x4 expected = Matrix4x4Helper::CreateRotationY(angle);
                Matrix4x4 actual = Matrix4x4Helper::CreateFromQuaternion(quat);
                Assert::IsTrue(Equal(expected, actual),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");

                // make sure convert back to quaternion is same as we passed QuaternionHelper::
                Quaternion q2 = QuaternionHelper::CreateFromRotationMatrix(actual);
                Assert::IsTrue(EqualRotation(quat, q2),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");
            }
        }

        // A test for FromQuaternion (Matrix4x4)
        TEST_METHOD(Matrix4x4FromQuaternionTest4)
        {
            for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
            {
                Quaternion quat = QuaternionHelper::CreateFromAxisAngle(Vector3Helper::UnitZ, angle);

                Matrix4x4 expected = Matrix4x4Helper::CreateRotationZ(angle);
                Matrix4x4 actual = Matrix4x4Helper::CreateFromQuaternion(quat);
                Assert::IsTrue(Equal(expected, actual),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");

                // make sure convert back to quaternion is same as we passed QuaternionHelper::
                Quaternion q2 = QuaternionHelper::CreateFromRotationMatrix(actual);
                Assert::IsTrue(EqualRotation(quat, q2),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");
            }
        }

        // A test for FromQuaternion (Matrix4x4)
        TEST_METHOD(Matrix4x4FromQuaternionTest5)
        {
            for (float angle = 0.0f; angle < 720.0f; angle += 10.0f)
            {
                Quaternion quat =
                    QuaternionHelper::Multiply(
                        QuaternionHelper::Multiply(
                            QuaternionHelper::CreateFromAxisAngle(Vector3Helper::UnitZ, angle),
                            QuaternionHelper::CreateFromAxisAngle(Vector3Helper::UnitY, angle)
                        ),
                        QuaternionHelper::CreateFromAxisAngle(Vector3Helper::UnitX, angle)
                    );

                Matrix4x4 expected =
                    Matrix4x4Helper::Multiply(
                        Matrix4x4Helper::Multiply(
                            Matrix4x4Helper::CreateRotationX(angle),
                            Matrix4x4Helper::CreateRotationY(angle)
                        ),
                        Matrix4x4Helper::CreateRotationZ(angle)
                    );
                Matrix4x4 actual = Matrix4x4Helper::CreateFromQuaternion(quat);
                Assert::IsTrue(Equal(expected, actual),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");

                // make sure convert back to quaternion is same as we passed QuaternionHelper::
                Quaternion q2 = QuaternionHelper::CreateFromRotationMatrix(actual);
                Assert::IsTrue(EqualRotation(quat, q2),
                    L"QuaternionHelper::FromQuaternion did not return the expected value.");
            }
        }

        // A test for Add (Matrix4x4, Matrix4x4)
        TEST_METHOD(Matrix4x4AddTest)
        {
            Matrix4x4 a = GenerateMatrixNumberFrom1To16();
            Matrix4x4 b = GenerateMatrixNumberFrom1To16();

            Matrix4x4 expected;
            expected.M11 = a.M11 + b.M11; expected.M12 = a.M12 + b.M12; expected.M13 = a.M13 + b.M13; expected.M14 = a.M14 + b.M14;
            expected.M21 = a.M21 + b.M21; expected.M22 = a.M22 + b.M22; expected.M23 = a.M23 + b.M23; expected.M24 = a.M24 + b.M24;
            expected.M31 = a.M31 + b.M31; expected.M32 = a.M32 + b.M32; expected.M33 = a.M33 + b.M33; expected.M34 = a.M34 + b.M34;
            expected.M41 = a.M41 + b.M41; expected.M42 = a.M42 + b.M42; expected.M43 = a.M43 + b.M43; expected.M44 = a.M44 + b.M44;

            Matrix4x4 actual;

            actual = Matrix4x4Helper::Add(a, b);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::Add did not return the expected value.");
        }

        // A test for Multiply (Matrix4x4, Matrix4x4)
        TEST_METHOD(Matrix4x4MultiplyTest3)
        {
            Matrix4x4 a = GenerateMatrixNumberFrom1To16();
            Matrix4x4 b = GenerateMatrixNumberFrom1To16();

            Matrix4x4 expected;
            expected.M11 = a.M11 * b.M11 + a.M12 * b.M21 + a.M13 * b.M31 + a.M14 * b.M41;
            expected.M12 = a.M11 * b.M12 + a.M12 * b.M22 + a.M13 * b.M32 + a.M14 * b.M42;
            expected.M13 = a.M11 * b.M13 + a.M12 * b.M23 + a.M13 * b.M33 + a.M14 * b.M43;
            expected.M14 = a.M11 * b.M14 + a.M12 * b.M24 + a.M13 * b.M34 + a.M14 * b.M44;

            expected.M21 = a.M21 * b.M11 + a.M22 * b.M21 + a.M23 * b.M31 + a.M24 * b.M41;
            expected.M22 = a.M21 * b.M12 + a.M22 * b.M22 + a.M23 * b.M32 + a.M24 * b.M42;
            expected.M23 = a.M21 * b.M13 + a.M22 * b.M23 + a.M23 * b.M33 + a.M24 * b.M43;
            expected.M24 = a.M21 * b.M14 + a.M22 * b.M24 + a.M23 * b.M34 + a.M24 * b.M44;

            expected.M31 = a.M31 * b.M11 + a.M32 * b.M21 + a.M33 * b.M31 + a.M34 * b.M41;
            expected.M32 = a.M31 * b.M12 + a.M32 * b.M22 + a.M33 * b.M32 + a.M34 * b.M42;
            expected.M33 = a.M31 * b.M13 + a.M32 * b.M23 + a.M33 * b.M33 + a.M34 * b.M43;
            expected.M34 = a.M31 * b.M14 + a.M32 * b.M24 + a.M33 * b.M34 + a.M34 * b.M44;

            expected.M41 = a.M41 * b.M11 + a.M42 * b.M21 + a.M43 * b.M31 + a.M44 * b.M41;
            expected.M42 = a.M41 * b.M12 + a.M42 * b.M22 + a.M43 * b.M32 + a.M44 * b.M42;
            expected.M43 = a.M41 * b.M13 + a.M42 * b.M23 + a.M43 * b.M33 + a.M44 * b.M43;
            expected.M44 = a.M41 * b.M14 + a.M42 * b.M24 + a.M43 * b.M34 + a.M44 * b.M44;
            Matrix4x4 actual;
            actual = Matrix4x4Helper::Multiply(a, b);

            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::Multiply did not return the expected value.");
        }

        // A test for Multiply (Matrix4x4, float)
        TEST_METHOD(Matrix4x4MultiplyTest5)
        {
            Matrix4x4 a = GenerateMatrixNumberFrom1To16();
            Matrix4x4 expected = Matrix4x4Helper::FromValues(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48);
            Matrix4x4 actual = Matrix4x4Helper::MultiplyByScalar(a, 3);

            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::Multiply did not return the expected value.");
        }

        // A test for Negate (Matrix4x4)
        TEST_METHOD(Matrix4x4NegateTest)
        {
            Matrix4x4 m = GenerateMatrixNumberFrom1To16();

            Matrix4x4 expected;
            expected.M11 = -1.0f; expected.M12 = -2.0f; expected.M13 = -3.0f; expected.M14 = -4.0f;
            expected.M21 = -5.0f; expected.M22 = -6.0f; expected.M23 = -7.0f; expected.M24 = -8.0f;
            expected.M31 = -9.0f; expected.M32 = -10.0f; expected.M33 = -11.0f; expected.M34 = -12.0f;
            expected.M41 = -13.0f; expected.M42 = -14.0f; expected.M43 = -15.0f; expected.M44 = -16.0f;
            Matrix4x4 actual;

            actual = Matrix4x4Helper::Negate(m);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::Negate did not return the expected value.");
        }

        // A test for Subtract (Matrix4x4, Matrix4x4)
        TEST_METHOD(Matrix4x4SubtractTest)
        {
            Matrix4x4 a = GenerateMatrixNumberFrom1To16();
            Matrix4x4 b = GenerateMatrixNumberFrom1To16();
            Matrix4x4 expected = Matrix4x4Helper::FromValues(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            Matrix4x4 actual;

            actual = Matrix4x4Helper::Subtract(a, b);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::Subtract did not return the expected value.");
        }

        void CreateBillboardTestMethod(Vector3 placeDirection, Vector3 cameraUpVector, Matrix4x4 expectedRotation)
        {
            Vector3 cameraPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 objectPosition = Vector3Helper::Add(cameraPosition, Vector3Helper::MultiplyByScalar(placeDirection, 10.0f));
            Matrix4x4 expected = Matrix4x4Helper::Multiply(expectedRotation, Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateBillboard(objectPosition, cameraPosition, cameraUpVector, Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateBillboard did not return the expected value.");
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest01)
        {
            // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest02)
        {
            // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, 0, 1), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(0)));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest03)
        {
            // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(1, 0, 0), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(90)));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest04)
        {
            // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(-1, 0, 0), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(-90)));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest05)
        {
            // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, 1, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(180))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest06)
        {
            // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, -1, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(0))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest07)
        {
            // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(1, 0, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest08)
        {
            // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(-1, 0, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(-90.0f))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest09)
        {
            // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, 1, 0), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(-90.0f))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest10)
        {
            // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, -1, 0), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(90.0f))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest11)
        {
            // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(180.0f))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTest12)
        {
            // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateBillboardTestMethod(Vector3Helper::FromValues(0, 0, 1), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(0.0f))));
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTooCloseTest1)
        {
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 cameraPosition = objectPosition;
            Vector3 cameraUpVector = Vector3Helper::FromValues(0, 1, 0);

            // Doesn't pass camera face direction. CreateBillboard uses Vector3(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateBillboard(objectPosition, cameraPosition, cameraUpVector, Vector3Helper::FromValues(0, 0, 1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateBillboard did not return the expected value.");
        }

        // A test for CreateBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateBillboardTooCloseTest2)
        {
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 cameraPosition = objectPosition;
            Vector3 cameraUpVector = Vector3Helper::FromValues(0, 1, 0);

            // Passes Vector3Helper::Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(-90.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateBillboard(objectPosition, cameraPosition, cameraUpVector, Vector3Helper::FromValues(1, 0, 0));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateBillboard did not return the expected value.");
        }

        void CreateConstrainedBillboardTestMethod(Vector3 placeDirection, Vector3 rotateAxis, Matrix4x4 expectedRotation)
        {
            Vector3 cameraPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 objectPosition = Vector3Helper::Add(cameraPosition, Vector3Helper::MultiplyByScalar(placeDirection, 10.0f));
            Matrix4x4 expected = Matrix4x4Helper::Multiply(expectedRotation, Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");

            // When you move camera along rotateAxis, result must be same.
            cameraPosition = Vector3Helper::Add(cameraPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 10.0f));
            actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");

            cameraPosition = Vector3Helper::Subtract(cameraPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 30.0f));
            actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest01)
        {
            // Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest02)
        {
            // Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, 0, 1), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(0)));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest03)
        {
            // Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(1, 0, 0), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(90)));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest04)
        {
            // Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(-1, 0, 0), Vector3Helper::FromValues(0, 1, 0), Matrix4x4Helper::CreateRotationY(ToRadians(-90)));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest05)
        {
            // Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, 1, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(180))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest06)
        {
            // Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, -1, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(0))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest07)
        {
            // Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(1, 0, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest08)
        {
            // Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(-1, 0, 0), Vector3Helper::FromValues(0, 0, 1),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(-90.0f))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest09)
        {
            // Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, 1, 0), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(-90.0f))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest10)
        {
            // Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, -1, 0), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(90.0f))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest11)
        {
            // Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(180.0f))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTest12)
        {
            // Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
            CreateConstrainedBillboardTestMethod(Vector3Helper::FromValues(0, 0, 1), Vector3Helper::FromValues(-1, 0, 0),
                Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationZ(ToRadians(90.0f)), Matrix4x4Helper::CreateRotationX(ToRadians(0.0f))));
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTooCloseTest1)
        {
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 cameraPosition = objectPosition;
            Vector3 cameraUpVector = Vector3Helper::FromValues(0, 1, 0);

            // Doesn't pass camera face direction. CreateConstrainedBillboard uses Vector3(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, Vector3Helper::FromValues(0, 0, 1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardTooCloseTest2)
        {
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 cameraPosition = objectPosition;
            Vector3 cameraUpVector = Vector3Helper::FromValues(0, 1, 0);

            // Passes Vector3Helper::Rgiht as camera face direction. Result must be same as -90 degrees rotate along y-axis.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(-90.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, Vector3Helper::FromValues(1, 0, 0), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardAlongAxisTest1)
        {
            // Place camera at up side of object.
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 rotateAxis = Vector3Helper::FromValues(0, 1, 0);
            Vector3 cameraPosition = Vector3Helper::Add(objectPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 10.0f));

            // In this case, CreateConstrainedBillboard picks Vector3(0, 0, -1) as object forward vector.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardAlongAxisTest2)
        {
            // Place camera at up side of object.
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 rotateAxis = Vector3Helper::FromValues(0, 0, -1);
            Vector3 cameraPosition = Vector3Helper::Add(objectPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 10.0f));

            // In this case, CreateConstrainedBillboard picks Vector3(1, 0, 0) as object forward vector.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(-90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(-90.0f))), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardAlongAxisTest3)
        {
            // Place camera at up side of object.
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 rotateAxis = Vector3Helper::FromValues(0, 1, 0);
            Vector3 cameraPosition = Vector3Helper::Add(objectPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 10.0f));

            // User passes correct objectForwardVector.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardAlongAxisTest4)
        {
            // Place camera at up side of object.
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 rotateAxis = Vector3Helper::FromValues(0, 1, 0);
            Vector3 cameraPosition = Vector3Helper::Add(objectPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 10.0f));

            // User passes correct objectForwardVector.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationY(ToRadians(180.0f)), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 1, 0));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateConstrainedBillboard (Vector3, Vector3, Vector3, Vector3?)
        TEST_METHOD(Matrix4x4CreateConstrainedBillboardAlongAxisTest5)
        {
            // Place camera at up side of object.
            Vector3 objectPosition = Vector3Helper::FromValues(3.0f, 4.0f, 5.0f);
            Vector3 rotateAxis = Vector3Helper::FromValues(0, 0, -1);
            Vector3 cameraPosition = Vector3Helper::Add(objectPosition, Vector3Helper::MultiplyByScalar(rotateAxis, 10.0f));

            // In this case, CreateConstrainedBillboard picks Vector3Helper::Right as object forward vector.
            Matrix4x4 expected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateRotationX(ToRadians(-90.0f)), Matrix4x4Helper::CreateRotationZ(ToRadians(-90.0f))), Matrix4x4Helper::CreateTranslation(objectPosition));
            Matrix4x4 actual = Matrix4x4Helper::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, Vector3Helper::FromValues(0, 0, -1), Vector3Helper::FromValues(0, 0, -1));
            Assert::IsTrue(Equal(expected, actual), L"Matrix4x4Helper::CreateConstrainedBillboard did not return the expected value.");
        }

        // A test for CreateScale (float)
        TEST_METHOD(Matrix4x4CreateScaleTest2)
        {
            float scale = 2.0f;
            Matrix4x4 expected = Matrix4x4Helper::FromValues(
                2.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 2.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 2.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
            Matrix4x4 actual = Matrix4x4Helper::CreateScale(scale);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::CreateScale did not return the expected value.");
        }

        // A test for CreateScale (float, float, float)
        TEST_METHOD(Matrix4x4CreateScaleTest3)
        {
            float xScale = 2.0f;
            float yScale = 3.0f;
            float zScale = 4.0f;
            Matrix4x4 expected = Matrix4x4Helper::FromValues(
                2.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 3.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 4.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
            Matrix4x4 actual = Matrix4x4Helper::CreateScale(xScale, yScale, zScale);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::CreateScale did not return the expected value.");
        }

        // A test for CreateScale (float, float, float, Vector3)
        TEST_METHOD(Matrix4x4CreateScaleCenterTest3)
        {
            Vector3 scale = Vector3Helper::FromValues(3, 4, 5);
            Vector3 center = Vector3Helper::FromValues(23, 42, 666);

            Matrix4x4 scaleAroundZero = Matrix4x4Helper::CreateScale(scale.X, scale.Y, scale.Z, Vector3Helper::Zero);
            Matrix4x4 scaleAroundZeroExpected = Matrix4x4Helper::CreateScale(scale.X, scale.Y, scale.Z);
            Assert::IsTrue(Equal(scaleAroundZero, scaleAroundZeroExpected));

            Matrix4x4 scaleAroundCenter = Matrix4x4Helper::CreateScale(scale.X, scale.Y, scale.Z, center);
            Matrix4x4 scaleAroundCenterExpected = Matrix4x4Helper::Multiply(Matrix4x4Helper::Multiply(Matrix4x4Helper::CreateTranslation(Vector3Helper::Negate(center)), Matrix4x4Helper::CreateScale(scale.X, scale.Y, scale.Z)), Matrix4x4Helper::CreateTranslation(center));
            Assert::IsTrue(Equal(scaleAroundCenter, scaleAroundCenterExpected));
        }

        // A test for CreateTranslation (Vector3)
        TEST_METHOD(Matrix4x4CreateTranslationTest1)
        {
            Vector3 position = Vector3Helper::FromValues(2.0f, 3.0f, 4.0f);
            Matrix4x4 expected = Matrix4x4Helper::FromValues(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                2.0f, 3.0f, 4.0f, 1.0f);

            Matrix4x4 actual = Matrix4x4Helper::CreateTranslation(position);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::CreateTranslation did not return the expected value.");
        }

        // A test for CreateTranslation (float, float, float)
        TEST_METHOD(Matrix4x4CreateTranslationTest2)
        {
            float xPosition = 2.0f;
            float yPosition = 3.0f;
            float zPosition = 4.0f;

            Matrix4x4 expected = Matrix4x4Helper::FromValues(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                2.0f, 3.0f, 4.0f, 1.0f);

            Matrix4x4 actual = Matrix4x4Helper::CreateTranslation(xPosition, yPosition, zPosition);
            Assert::AreEqual(expected, actual, L"Matrix4x4Helper::CreateTranslation did not return the expected value.");
        }

        // A test for Translation
        TEST_METHOD(Matrix4x4TranslationTest)
        {
            Matrix4x4 a = GenerateTestMatrix();
            Matrix4x4 b = a;

            // Transfomed vector that has same semantics of property must be same.
            Vector3 val = Vector3Helper::FromValues(a.M41, a.M42, a.M43);
            Assert::AreEqual(val, Matrix4x4Helper::Translation(a), L"Matrix4x4Helper::Translation was not set correctly.");
        }

        // A test for IsIdentity()
        TEST_METHOD(Matrix4x4IsIdentityTest)
        {
            Assert::IsTrue(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::Identity));
            Assert::IsTrue(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1)));
            Assert::IsFalse(Matrix4x4Helper::IsIdentity(Matrix4x4Helper::FromValues(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0)));
        }

        // A test for Matrix4x4 (Matrix3x2)
        TEST_METHOD(Matrix4x4From3x2Test)
        {
            Matrix3x2 source = Matrix3x2Helper::FromValues(1, 2, 3, 4, 5, 6);
            Matrix4x4 result = Matrix4x4Helper::FromMatrix3x2(source);

            Assert::AreEqual(source.M11, result.M11);
            Assert::AreEqual(source.M12, result.M12);
            Assert::AreEqual(0.0f, result.M13);
            Assert::AreEqual(0.0f, result.M14);

            Assert::AreEqual(source.M21, result.M21);
            Assert::AreEqual(source.M22, result.M22);
            Assert::AreEqual(0.0f, result.M23);
            Assert::AreEqual(0.0f, result.M24);

            Assert::AreEqual(0.0f, result.M31);
            Assert::AreEqual(0.0f, result.M32);
            Assert::AreEqual(1.0f, result.M33);
            Assert::AreEqual(0.0f, result.M34);

            Assert::AreEqual(source.M31, result.M41);
            Assert::AreEqual(source.M32, result.M42);
            Assert::AreEqual(0.0f, result.M43);
            Assert::AreEqual(1.0f, result.M44);
        }

        struct Matrix4x4_2x
        {
            Matrix4x4 a;
            Matrix4x4 b;
        };

        struct Matrix4x4PlusFloat
        {
            Matrix4x4 v;
            float f;
        };

        struct Matrix4x4PlusFloat_2x
        {
            Matrix4x4PlusFloat a;
            Matrix4x4PlusFloat b;
        };

        // A test to make sure these types are blittable directly into GPU buffer memory layouts
        TEST_METHOD(Matrix4x4SizeofTest)
        {
            Assert::AreEqual(size_t(64), sizeof(Matrix4x4));
            Assert::AreEqual(size_t(128), sizeof(Matrix4x4_2x));
            Assert::AreEqual(size_t(68), sizeof(Matrix4x4PlusFloat));
            Assert::AreEqual(size_t(136), sizeof(Matrix4x4PlusFloat_2x));
        }

        // A test to make sure the fields are laid out how we expect
        TEST_METHOD(Matrix4x4FieldOffsetTest)
        {
            Assert::AreEqual(size_t(0), offsetof(Matrix4x4, M11));
            Assert::AreEqual(size_t(4), offsetof(Matrix4x4, M12));
            Assert::AreEqual(size_t(8), offsetof(Matrix4x4, M13));
            Assert::AreEqual(size_t(12), offsetof(Matrix4x4, M14));

            Assert::AreEqual(size_t(16), offsetof(Matrix4x4, M21));
            Assert::AreEqual(size_t(20), offsetof(Matrix4x4, M22));
            Assert::AreEqual(size_t(24), offsetof(Matrix4x4, M23));
            Assert::AreEqual(size_t(28), offsetof(Matrix4x4, M24));

            Assert::AreEqual(size_t(32), offsetof(Matrix4x4, M31));
            Assert::AreEqual(size_t(36), offsetof(Matrix4x4, M32));
            Assert::AreEqual(size_t(40), offsetof(Matrix4x4, M33));
            Assert::AreEqual(size_t(44), offsetof(Matrix4x4, M34));

            Assert::AreEqual(size_t(48), offsetof(Matrix4x4, M41));
            Assert::AreEqual(size_t(52), offsetof(Matrix4x4, M42));
            Assert::AreEqual(size_t(56), offsetof(Matrix4x4, M43));
            Assert::AreEqual(size_t(60), offsetof(Matrix4x4, M44));
        }
    };
}