-- 코드를 입력하세요
SELECT 
    ANIMAL_ID, NAME, 
    IF(SEX_UPON_INTAKE like "%Neutered%" or SEX_UPON_INTAKE like "%Spayed%", 'O', 'X') as 중성화
FROM ANIMAL_INS;