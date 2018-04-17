/*

NARTool

*/

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////
//                 //
//    Constants    //
//                 //
/////////////////////
const char* help_string =
"Options:\n"
"  -h: Display this help.\n"
"  -v: Display version.\n"
"  -A [ARCHIVE]: Set the current archive. If it does not exist, it will be created if necessary.\n"
"  -a [FILES]: Add the specified files to the current archive, but do not replace existing files.\n"
"  -r [FILES]: Add the specified files to the current archive, replacing existing files.\n"
"  -x: Extract the files in the current archive.\n"
"  -l: List all files in the current archive.\n"
"Examples:\n"
"  nartool -A archive.nar -x : Extract files in archive.nar.\n"
"  nartool -A archive.nar -a file1.txt file2.txt file3.txt : Adds files file1.txt, file2.txt and file3.txt to archive.nar.\n"
"  nartool -A archive.nar -l : Lists the files in archive.nar.\n"
"Notes:\n"
"  All options are processed in the order they are provided on the command line.\n";

#define NARTOOL_VERSION_MAJOR 0
#define NARTOOL_VERSION_MINOR 0
#define NARTOOL_VERSION_REVISION 1

///////////////////////
//                   //
//    Definitions    //
//                   //
///////////////////////
typedef enum {
  NARTOOL_COMMAND_NONE,
  NARTOOL_COMMAND_HELP,
  NARTOOL_COMMAND_VERSION,
  NARTOOL_COMMAND_SET_ARCHIVE,
  NARTOOL_COMMAND_ADD,
  NARTOOL_COMMAND_REPLACE,
  NARTOOL_COMMAND_EXTRACT,
  NARTOOL_COMMAND_LIST
} NARToolCommandType;

typedef struct {
  NARToolCommandType type;
  char* arg;
} NARToolCommand;

///////////////////
//               //
//    Globals    //
//               //
///////////////////
char* current_archive = NULL;
FILE* current_archive_file = NULL;

/////////////////////
//                 //
//    Functions    //
//                 //
/////////////////////
void add_command(NARToolCommand** commands, size_t* num_commands, NARToolCommand command) {
  (*num_commands)++;
  *commands = realloc(*commands, *num_commands * sizeof(NARToolCommand));
  *commands[*num_commands - 1] = command;
}

void verify_nar_header(FILE* file) {

  fseek(file, 0, SEEK_END);
  size_t length = ftell(file);
  
  if (length == 0) {

    uint8_t header[] = { 'N', 'A', 'R', 0x01, 0x00, 0x00, 0x00, 0x00 };
    fwrite(header, 1, 8, file);

  } else if (length >= 8) {

    rewind(file);
    uint8_t header_and_version[4];
    fread(header_and_version, 1, 4, file);

    if (memcmp(header_and_version, "NAR", 3) != 0) {
      fprintf(stderr, "Error: Specified archive is not valid and is not empty (invalid header).\n");
      exit(1);
    }

    if (header_and_version[4] != 0x01) {
      fprintf(stderr, "Error: Specified archive has an invalid version.\n");
      exit(1);
    }

  } else {
    fprintf(stderr, "Error: Specified archive is not valid and is not empty (too short to be a valid file).\n");
    exit(1);
  }
}

////////////////////////////
//                        //
//    Argument Parsing    //
//                        //
////////////////////////////
NARToolCommand* parse_args(int argc, char** argv, size_t* num_commands) {

  NARToolCommand* commands = NULL;

  NARToolCommandType current_type = NARTOOL_COMMAND_NONE;

  for (int i = 1; i < argc; i++) {

    if (argv[i][0] == '-') {

      switch (argv[i][1]) {
        case 'h': {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_HELP;
          add_command(&commands, num_commands, command);
          break;
        }
        case 'v': {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_VERSION;
          add_command(&commands, num_commands, command);
          break;
        }
        case 'A': {
          current_type = NARTOOL_COMMAND_SET_ARCHIVE;
          break;
        }
        case 'a': {
          current_type = NARTOOL_COMMAND_ADD;
          break;
        }
        case 'r': {
          current_type = NARTOOL_COMMAND_REPLACE;
          break;
        }
        case 'x': {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_EXTRACT;
          add_command(&commands, num_commands, command);
          break;
        }
        case 'l': {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_LIST;
          add_command(&commands, num_commands, command);
          break;
        }
      }

    } else {

      switch (current_type) {
        case NARTOOL_COMMAND_SET_ARCHIVE: {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_SET_ARCHIVE;
          command.arg = argv[i];
          add_command(&commands, num_commands, command);
          current_type = NARTOOL_COMMAND_NONE;
          break;
        }
        case NARTOOL_COMMAND_ADD: {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_ADD;
          command.arg = argv[i];
          add_command(&commands, num_commands, command);
          break;
        }
        case NARTOOL_COMMAND_REPLACE: {
          NARToolCommand command;
          command.type = NARTOOL_COMMAND_REPLACE;
          command.arg = argv[i];
          add_command(&commands, num_commands, command);
          break;
        }
        default: {
          fprintf(stderr, "Error: Invalid non-option %s.\n", argv[i]);
          exit(EXIT_FAILURE);
          break;
        }
      }
      
    }

  }

  return commands;

}

///////////////////////////
//                       //
//    Command Running    //
//                       //
///////////////////////////
void run_commands(NARToolCommand* commands, size_t num_commands) {

  for (size_t i = 0; i < num_commands; i++) {
    switch (commands[i].type) {
    
      case NARTOOL_COMMAND_HELP: {
        printf("%s", help_string);
        break;
      }
      
      case NARTOOL_COMMAND_VERSION: {
        printf("nartool v%i.%i.%i\n", NARTOOL_VERSION_MAJOR, NARTOOL_VERSION_MINOR, NARTOOL_VERSION_REVISION);
        break;
      }
      
      case NARTOOL_COMMAND_SET_ARCHIVE: {
        current_archive = commands[i].arg;
        current_archive_file = fopen(commands[i].arg, "r+b");

        if (errno == ENOENT) {
          current_archive_file = fopen(commands[i].arg, "w");
          fclose(current_archive_file);
          current_archive_file = fopen(commands[i].arg, "r+b");
        }

        if (!current_archive_file) {
          fprintf(stderr, "Error: File '%s' could not be opened (%s).\n", commands[i].arg, strerror(errno));
          exit(1);
        }

        verify_nar_header(current_archive_file);

        break;
      }
      
      // These two are very similar so they are bunched together and separated later on. Not great, but it works™.
      case NARTOOL_COMMAND_ADD:
      case NARTOOL_COMMAND_REPLACE: {

        if (!current_archive) {
          fprintf(stderr, "Error: Add or replace operation requested without a current archive being specified.\n");
          exit(1);
        }

        break;
      }
      
      default: {
        fprintf(stderr, "Error: Unhandled command %x; this should not happen.\n", commands[i].type);
        exit(1);
        break;
      }
      
    }
  }

}

/////////////////////////
//                     //
//    Main Function    //
//                     //
/////////////////////////
int main(int argc, char** argv) {

  size_t num_commands = 0;
  NARToolCommand* commands = parse_args(argc, argv, &num_commands);

  run_commands(commands, num_commands);

  return 0;

}
