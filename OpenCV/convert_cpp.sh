#!/bin/bash

# 현재 디렉토리부터 모든 하위 디렉토리에서 확장자가 .cpp인 파일을 찾고,
# 널 문자(\0)로 구분하여 안전하게 파일명을 처리
find . -type f -name "*.cpp" -print0 | while IFS= read -r -d '' file
do
  # 파일의 디렉토리 경로 추출 (예: ./foo/bar/main.cpp -> ./foo/bar)
  dir=$(dirname "$file")
  # 파일명만 추출 (예: ./foo/bar/main.cpp -> main.cpp)
  base=$(basename "$file")
  # 임시파일명 지정: 각 파일이 속한 디렉토리에 프로세스 ID 기반 임시파일 생성
  temp_file="$dir/.tmp_convert_$$.tmp"  # $$는 현재 쉘 프로세스 ID

  # 변환할 파일 경로 출력
  echo "Converting '$file'..."

  # iconv 명령으로 cp949에서 utf-8로 인코딩 변환 실행
  # 변환 결과를 임시파일에 저장
  if iconv -f cp949 -t utf-8 "$file" > "$temp_file"; then
    # 변환 성공 시, 임시파일을 원본 파일명으로 덮어쓰기
    mv "$temp_file" "$file"
    echo "Converted successfully."
  else
    # 변환 실패 시, 임시파일 삭제하고 원본 파일 유지
    echo "Conversion failed for '$file'. Skipping."
    rm -f "$temp_file"
  fi
done