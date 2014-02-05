/* 
 * File:   Parameters.h
 * Author: andrey
 *
 * Created on 5 ?????? 2014, 9:44
 * contains methods for can parameters processing
 */

/**
 * @author Kyrylov Andrii
 * @param char* - new parameter name
 * @param char - new parameter type
 * @param char* - parameter value array
 * @param unsigned int - byte count in value array
 * @todo make new parameter in fat structure
 * @return 1 - parameter was added;
 * 0 - there is not enough space
 */
char AddParameter(char*, char, char*, unsigned int);
/**
 * @author Liutyi Ievgen
 * @todo find max index among existing parameter's descriptors
 * @return max index
 */
unsigned int FindMaxIndex();