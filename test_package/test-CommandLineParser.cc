#include <gtest/gtest.h>


#include <fcdk/CommandLineParser.h>
#include "ArgvHelper.h"


TEST( CommandLineParserPrecondition, duplicate_short_option_throw_logical_error )
{
  FCDK::CommandLineOptionFlag help1( 'h', "help", "help message" );
  FCDK::CommandLineOptionFlag help2( 'h', "Re Help", "Re help message" );
  std::vector<FCDK::CommandLineOption*> accepted_options{ &help1, &help2 };
  ASSERT_THROW( FCDK::CommandLineParser parser( accepted_options ), FCDK::RuntimeError );
}


TEST( CommandLineParserPrecondition, duplicate_long_option_throw_logical_error )
{
  FCDK::CommandLineOptionFlag help1( 'h', "help", "help message" );
  FCDK::CommandLineOptionFlag help2( 'b', "help", "Re help message" );
  std::vector<FCDK::CommandLineOption*> accepted_options{ &help1, &help2 };
  ASSERT_THROW( FCDK::CommandLineParser parser( accepted_options ), FCDK::RuntimeError );
}


TEST( CommandLineParserPrecondition, empty_long_option_do_not_throw )
{
  FCDK::CommandLineOptionFlag help1( 'h', "", "help message" );
  FCDK::CommandLineOptionFlag help2( 'b', "", "Re help message" );
  std::vector<FCDK::CommandLineOption*> accepted_options{ &help1, &help2 };
  ASSERT_NO_THROW( FCDK::CommandLineParser parser( accepted_options ) );
}


TEST( CommandLineParserPrecondition, flag_are_initialized_to_false )
{
  FCDK::CommandLineOptionFlag help( 'h', "", "help message" );
  ASSERT_FALSE( help.getValue() );
}


// TODO: static_assert
TEST( CommandLineParserPrecondition, flag_are_convertiable_to_bool )
{
  FCDK::CommandLineOptionFlag help( 'h', "", "help message" );
  ASSERT_FALSE( help );
}


//------------------------------------------------------------------------------
class CommandLineParserFixture  : public  ::testing::Test
{
protected:
  CommandLineParserFixture()
    : help('h', "help", "message for help" )
    , debug('d', "debug", "message for debug" )
    , crash('c', "crash", "message for crash" )
    , verbosity('v', "verbosity", "verbosity level" )
    , user_name('u', "user", "user name" )
    , accepted_options{ &help, &debug, &crash, &verbosity, &user_name }
    , parser( accepted_options )
  {}

  FCDK::CommandLineOptionFlag help;
  FCDK::CommandLineOptionFlag debug;
  FCDK::CommandLineOptionFlag crash;
  FCDK::CommandLineOptionWithValue verbosity;
  FCDK::CommandLineOptionWithValue user_name;


  std::vector<FCDK::CommandLineOption*> accepted_options;
  FCDK::CommandLineParser parser;
};



TEST_F( CommandLineParserFixture, test_parse_return_1_when_command_line_is_empty )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name" };
  ASSERT_EQ( parser.parse( program_command_line.size(), program_command_line.argv() ), 1 );
}


TEST_F( CommandLineParserFixture, test_parse_throw_when_unknown_short_option )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-z" };
  ASSERT_THROW( parser.parse( program_command_line.size(), program_command_line.argv() ),
                FCDK::RuntimeError );
}


TEST_F( CommandLineParserFixture, test_parse_throw_when_unknown_long_option )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "--wrong-option" };
  ASSERT_THROW( parser.parse( program_command_line.size(), program_command_line.argv() ),
                FCDK::RuntimeError );
}


TEST_F( CommandLineParserFixture, test_parse_return_index_of_first_non_option__no_options )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "first_non_option",
                                               "second_non_option" };
  int first_non_option = parser.parse( program_command_line.size(), program_command_line.argv() );
  ASSERT_EQ( first_non_option, 1 );
}


TEST_F( CommandLineParserFixture, test_option_delimiter_ends_parsing )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "--",
                                               "first_non_option",
                                               "-h",
                                               "second_non_option" };
  int first_non_option = parser.parse( program_command_line.size(), program_command_line.argv() );
  ASSERT_EQ( first_non_option, 2 );
  ASSERT_FALSE( help );
}


TEST_F( CommandLineParserFixture, test_parse_flag )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-h" };
  parser.parse( program_command_line.size(), program_command_line.argv() );
  ASSERT_TRUE( help );
}


TEST_F( CommandLineParserFixture, test_parse_long_flag )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "--help" };
  parser.parse( program_command_line.size(), program_command_line.argv() );
  ASSERT_TRUE( help );
}


TEST_F( CommandLineParserFixture, test_parse_flag_block )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-hdc" };
  parser.parse( program_command_line.size(), program_command_line.argv() );
  ASSERT_TRUE( help );
  ASSERT_TRUE( debug );
  ASSERT_TRUE( crash );
}


TEST_F( CommandLineParserFixture, test_parse_option_with_value )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-v",
                                               "3"};
  parser.parse(program_command_line.size(), program_command_line.argv());
  ASSERT_EQ( verbosity.getValue(), "3" );
}


TEST_F( CommandLineParserFixture, test_parse_long_option_with_value )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "--verbosity",
                                               "3"};
  parser.parse(program_command_line.size(), program_command_line.argv());
  ASSERT_EQ( verbosity.getValue(), "3" );
}


TEST_F( CommandLineParserFixture, test_parse_option_with_value_not_last_throw )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-vdc",
                                               "3"};
  ASSERT_THROW(parser.parse(program_command_line.size(),
                            program_command_line.argv()),
               FCDK::RuntimeError);
}


TEST_F( CommandLineParserFixture, test_parse_option_with_value_should_be_last )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-dcv",
                                               "3"};
  parser.parse(program_command_line.size(), program_command_line.argv());
  ASSERT_EQ( verbosity.getValue(), "3" );
}


TEST_F( CommandLineParserFixture, test_parse_short_option_with_value_wihout_value_throw )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-v" };
  ASSERT_THROW( parser.parse(program_command_line.size(),
                             program_command_line.argv()),
                FCDK::RuntimeError );
}


TEST_F( CommandLineParserFixture, test_parse_short_option_block_with_value_wihout_value_throw )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "-hdcv" };
  ASSERT_THROW( parser.parse(program_command_line.size(),
                             program_command_line.argv()),
                FCDK::RuntimeError );
}


TEST_F( CommandLineParserFixture, test_parse_long_option_with_value_wihout_value_throw )
{
  FCDK::Test::ArgvHelper program_command_line{ "program_name",
                                               "--verbosity" };
  ASSERT_THROW( parser.parse(program_command_line.size(),
                             program_command_line.argv()),
                FCDK::RuntimeError );
}
