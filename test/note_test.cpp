//
// Created by nekita on 01.09.25.
//

#include <gtest/gtest.h>

#include "netodo/notes/Note.hpp"

TEST(NoteTest, InitTest) {
    Note note("hello");
    ASSERT_EQ(note.description, "Description for Note hello");
    Note note_("1234567890123");
    ASSERT_EQ(note_.short_name, "1234567890");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
