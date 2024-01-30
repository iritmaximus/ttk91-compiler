module Main (main) where

import System.Environment
import Parser

main :: IO ()
main = do args <- getArgs
          putStrLn . readExpr $ args !! 0

readExpr :: String -> String
readExpr str = 
    case parseToken str of
        Left err -> "No match: " ++ show err
        Right val -> show val
