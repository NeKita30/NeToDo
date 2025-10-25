//
// Created by nekita on 25.10.25.
//

#include <gtest/gtest.h>
#include "netodo/exceptions/CustomException.hpp"
#include "netodo/exceptions/ExceptionBuilder.hpp"
#include "netodo/exceptions/Exceptions.hpp"

TEST(ExceptionTest, CustomException) {
    EXPECT_THROW(
            {
                try {
                    throw CustomException("Hello");
                } catch (const CustomException& e) {
                    EXPECT_STREQ( "Hello", e.what() );
                    throw;
                }
            }, CustomException);

}

TEST(ExceptionTest, ExceptionBuilder) {
    EXPECT_THROW(
            {
                try {
                    ExceptionBuilder error;
                    throw error.WithMessage("Error")
                               .AtLine(10)
                               .InModule("Module")
                               .Build();
                } catch (const CustomException& e) {
                    EXPECT_STREQ("Error\n"
                                 "In module: Module\n"
                                 "At line: 10", e.what());
                    throw;
                }
            }, CustomException);
}

TEST(ExceptionTest, TypedExceptionBuilder) {
    EXPECT_THROW(
        {
            try {
                ExceptionBuilder error;
                throw error.WithMessage("DB Error")
                           .Build<DBException>();
            } catch (const DBException& e) {
                EXPECT_STREQ("DB Error", e.what());
                throw;
            }
        }, DBException);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
