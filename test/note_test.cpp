//
// Created by nekita on 01.09.25.
//

#include <gtest/gtest.h>

#include "netodo/notes/Note.hpp"
#include "netodo/notes/Task.hpp"
#include "netodo/notes/ToDo.hpp"

TEST(NoteTest, InitTest) {
    Note note("hello");
    ASSERT_EQ(note.description, "Description for Note hello");
    Note note_("1234567890123");
}

TEST(NoteTest, ToDoTest) {
    ToDo td1(101, 102, "hello");
    ASSERT_EQ(td1.description, "Description for Note hello");

    ToDo td2("a");
    ASSERT_EQ(td2.status, NoteStatus::NotStarted);

    ToDo td3(101, 102, "abc", "ghi", NoteStatus::InProgress);
    ASSERT_EQ(td3.description, "ghi");
    ASSERT_EQ(td3.status, NoteStatus::InProgress);
}

TEST(NoteTest, TaskTest) {
    Task tk1(111, 122, "hello", "hello world",
        75, 100, {}, NoteStatus::NotStarted);
    ASSERT_EQ(tk1.description, "hello world");
    ASSERT_EQ(tk1.status, NoteStatus::NotStarted);

    Task tk2("hello");
    ASSERT_EQ(tk2.description, "Description for Note hello");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
