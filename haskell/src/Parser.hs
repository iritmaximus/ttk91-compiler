module Parser (
    parseToken, 
    parseRegister, 
    parseInstruction, 
    parseOperand, 
    Token ) where

import Data.Char
import Data.List.Split



parseToken :: String -> Either String Token
parseToken str = case parseOperand str of
                      Just token -> Right token
                      Nothing    -> Left "No token found"

parseRegister :: String -> Maybe Token
parseRegister (x:xs)
    | x == 'R' && not (null xs) && all isDigit xs = Just $ Register (read xs)
    | otherwise = Nothing



dataInsructions = ["LOAD", "STORE", "IN", "OUT"]
arithmeticInstructions = ["ADD", "SUB", "MUL", "DIV", "MOD"]
logicInstructions = ["AND", "OR", "XOR", "NOT", "SHL", "SHR", "SHRA", "COMP"]
branchingInstructions = ["JUMP", "JNEG", "JZER", "JPOS", "JNNEG", "JNZER", "JNPOS", "JLES", "JEQU", "JGRE", "JNLES", "JNEQU", "JNGRE"]
stackInstructions = ["PUSH", "POP", "PUSHR", "POPR"]
subroutineInstructions = ["CALL", "EXIT"]
systemcallInsructions = ["SVC"]
compilerInsructions = ["EQU", "DC", "DS", "DEF"]
otherInstructions = ["NOP"]

allInsructions = dataInsructions ++ arithmeticInstructions ++ logicInstructions ++ branchingInstructions ++ stackInstructions ++ subroutineInstructions ++ systemcallInsructions ++ compilerInsructions ++ otherInstructions

parseInstruction :: String -> Maybe Token
parseInstruction str = 
    if str `elem` allInsructions then
        Just $ Instruction str
    else 
        Nothing


variables = [Variable "X", Variable "Y"]

parseOperand :: String -> Maybe Token
parseOperand str = Just $ Operand str immediateOperand indirectOperand indexed
    where
        immediateOperand = '=' `elem` str
        indirectOperand = '@' `elem` str
        value = if immediateOperand || indirectOperand 
                then tail str
                else str

        indexed = '(' `elem` value && ')' `elem` value
        registers = if indexed 
                    then endBy "(" $ init value
                    else [str]





data Token = Register Int
           | Instruction String
           | Comment String
           | Operand String Bool Bool Bool
           | MemoryAddress String
           | Value Integer
           | Variable String
           | Error String
           deriving (Show, Eq)
