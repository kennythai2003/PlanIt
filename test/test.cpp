#include <gtest/gtest.h>
#include "../header/task.h"
#include "../header/date.h"
#include "../header/time.h"
#include "../header/UI.h"
#include "../header/debug.h"

TEST(TASKTEST, defaultConstructor)
{
    Task *newTask = new Task();

    ASSERT_EQ(newTask->getName(), "");
    ASSERT_EQ(newTask->getDescription(), "");

    ASSERT_EQ(newTask->getDate().getMonth(), 1);
    ASSERT_EQ(newTask->getDate().getDay(), 1);
    ASSERT_EQ(newTask->getDate().getYear(), 1);

    ASSERT_EQ(newTask->getStartTime().getHour(), 0); 
    ASSERT_EQ(newTask->getStartTime().getMinute(), 0);
    ASSERT_EQ(newTask->getEndTime().getHour(), 0); 
    ASSERT_EQ(newTask->getEndTime().getMinute(), 0); 

    ASSERT_FALSE(newTask->getPriority());   
}

TEST(TASKTEST, parameterConstructor)
{
    Task *newTask = new Task("birthday", "kenny's bday", Date(2, 14, 2003), Time(11, 11), Time(11, 59), true);

    EXPECT_EQ(newTask->getName(), "birthday");
    EXPECT_EQ(newTask->getDescription(), "kenny's bday");

    EXPECT_EQ(newTask->getDate().getMonth(), 2);
    EXPECT_EQ(newTask->getDate().getDay(), 14);
    EXPECT_EQ(newTask->getDate().getYear(), 2003);

    EXPECT_EQ(newTask->getStartTime().getHour(), 11); 
    EXPECT_EQ(newTask->getStartTime().getMinute(), 11);
    EXPECT_EQ(newTask->getEndTime().getHour(), 11); 
    EXPECT_EQ(newTask->getEndTime().getMinute(), 59); 

    EXPECT_TRUE(newTask->getPriority());   
}

TEST(TASKTEST, setterGetterNameAndDescription)
{
    Task *newTask = new Task();

    newTask->setName("task");
    newTask->setDescription("description");

    EXPECT_EQ(newTask->getName(), "task");
    EXPECT_EQ(newTask->getDescription(), "description");
}


TEST(TASKTEST, setterGetterDate)
{
    Task *newTask = new Task();

    newTask->setDate(3, 10, 2022);

    EXPECT_EQ(newTask->getDate().getMonth(), 3);
    EXPECT_EQ(newTask->getDate().getDay(), 10);
    EXPECT_EQ(newTask->getDate().getYear(), 2022);
}

TEST(TASKTEST, setterGetterStartAndEndTime)
{ 
    Task *newTask = new Task();

    newTask->setStartTime(3, 10);
    newTask->setEndTime(11, 59);

    EXPECT_EQ(newTask->getStartTime().getHour(), 3); 
    EXPECT_EQ(newTask->getStartTime().getMinute(), 10);
    EXPECT_EQ(newTask->getEndTime().getHour(), 11); 
    EXPECT_EQ(newTask->getEndTime().getMinute(), 59); 
}

TEST(TASKTEST, setterGetterPriority)
{
    Task *newTask = new Task();

    newTask->setPriority(true);

    EXPECT_EQ(newTask->getPriority(), true);     
}

TEST(TIMETEST, defaultConstructor)
{
    Time *newTime = new Time();

    ASSERT_EQ(newTime->getHour(), 0);
    ASSERT_EQ(newTime->getMinute(), 0);
}

TEST(TIMETEST, parameterConstructor)
{
    Time *newTime = new Time(11, 59);

    EXPECT_EQ(newTime->getHour(), 11);
    EXPECT_EQ(newTime->getMinute(), 59);
}

TEST(TIMETEST, settersGetters)
{
    Time *newTime = new Time();

    newTime->setHour(10);
    newTime->setMinute(10);

    EXPECT_EQ(newTime->getHour(), 10);
    EXPECT_EQ(newTime->getMinute(), 10);  
}

TEST(DATETEST, defaultConstructor)
{
    Date *newDate = new Date();

    ASSERT_EQ(newDate->getMonth(), 1);
    ASSERT_EQ(newDate->getDay(), 1); 
    ASSERT_EQ(newDate->getYear(), 1);
}

TEST(DATETEST, parameterConstructor)
{
    Date *newDate = new Date(10, 31, 2000);

    EXPECT_EQ(newDate->getMonth(), 10);
    EXPECT_EQ(newDate->getDay(), 31); 
    EXPECT_EQ(newDate->getYear(), 2000);
}

TEST(DATETEST, settersGetters)
{
    Date *newDate = new Date();

    newDate->setMonth(11);
    newDate->setDay(24);
    newDate->setYear(2022);

    EXPECT_EQ(newDate->getMonth(), 11);
    EXPECT_EQ(newDate->getDay(), 24); 
    EXPECT_EQ(newDate->getYear(), 2022);
}

TEST(DEBUGTEST, nonDigit)
{
    Debug newDebug;

    EXPECT_FALSE(newDebug.containsNonDigit("2029"));
    EXPECT_TRUE(newDebug.containsNonDigit("abc"));
}

TEST(DEBUGTEST, leapYear)
{
    Debug newDebug;

    EXPECT_FALSE(newDebug.checkLeapYear(-2024));
    EXPECT_FALSE(newDebug.checkLeapYear(2029));
    EXPECT_FALSE(newDebug.checkLeapYear(1800));
    EXPECT_TRUE(newDebug.checkLeapYear(2000));
    EXPECT_TRUE(newDebug.checkLeapYear(2004));
}

TEST(DEBUGTEST, validMonthDayYear)
{
    Debug newDebug;

    EXPECT_TRUE(newDebug.isValidMonth("12"));
    EXPECT_FALSE(newDebug.isValidMonth("0"));
    EXPECT_FALSE(newDebug.isValidMonth("-1"));

    EXPECT_TRUE(newDebug.isValidYear("1754"));
    EXPECT_FALSE(newDebug.isValidYear("0"));

    EXPECT_TRUE(newDebug.isValidDay("12", 2, 2020));
    EXPECT_FALSE(newDebug.isValidDay("-1", 0, 2020));
    EXPECT_FALSE(newDebug.isValidDay("0", 10, -1));

    EXPECT_TRUE(newDebug.isValidDay("29", 2, 2024));
    EXPECT_FALSE(newDebug.isValidDay("29", 2, 2023));
}

TEST(DEBUGTEST, validHourMinute)
{
    Debug newDebug;

    EXPECT_TRUE(newDebug.isValidHour("12"));
    EXPECT_FALSE(newDebug.isValidHour("24"));
    EXPECT_FALSE(newDebug.isValidHour("-1"));

    EXPECT_TRUE(newDebug.isValidMinute("12"));
    EXPECT_FALSE(newDebug.isValidMinute("60"));
    EXPECT_FALSE(newDebug.isValidMinute("-1"));
}

TEST(DEBUGTEST, validPriority)
{
    Debug newDebug;

    EXPECT_FALSE(newDebug.isValidPriority("N"));
    EXPECT_FALSE(newDebug.isValidPriority("Y"));
    EXPECT_FALSE(newDebug.isValidPriority("n"));
    EXPECT_FALSE(newDebug.isValidPriority("y"));
    EXPECT_TRUE(newDebug.isValidPriority("0"));
    EXPECT_TRUE(newDebug.isValidPriority("1"));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}