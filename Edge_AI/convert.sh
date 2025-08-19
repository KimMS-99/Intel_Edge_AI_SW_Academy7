#!/usr/bin/env bash
# CP949(MS949)로 인코딩된 파일만 UTF-8로 인플레이스 변환
# 사용법:
#   ./convert                # 기본: cpp c h hpp py md txt
#   ./convert md             # md만
#   ./convert md py          # md와 py만

set -euo pipefail

# 확장자 목록 결정
if [ "$#" -gt 0 ]; then
  exts=("$@")
else
  exts=(cpp c h hpp py md txt)
fi

# 제외할 디렉토리
excludes=(
  venv .venv env
  node_modules .yarn .pnpm-store vendor
  build dist out bin obj target CMakeFiles .gradle .mvn .next .nuxt .turbo public site
  __pycache__ .pytest_cache .mypy_cache .ruff_cache .cache .tox .ipynb_checkpoints
  .git .idea .vscode .vs
  DerivedData Pods Carthage .build
)

# find 조건 구성 (excludes는 prune)
find_args=(find . \( -type d \( )
first=1
for ex in "${excludes[@]}"; do
  if (( first )); then
    find_args+=(-name "$ex")
    first=0
  else
    find_args+=(-o -name "$ex")
  fi
done
find_args+=( \) -prune \) -o \( -type f \( )

first=1
for ext in "${exts[@]}"; do
  if (( first )); then
    find_args+=(-name "*.${ext}")
    first=0
  else
    find_args+=(-o -name "*.${ext}")
  fi
done
find_args+=( \) \) -print0 )

# 변환 루프
"${find_args[@]}" | while IFS= read -r -d '' file; do
  dir=$(dirname "$file")
  base=$(basename "$file")
  tmp="$(mktemp "${dir}/.tmp_convert_${base}.XXXXXX")" || { echo "임시파일 생성 실패: $file"; continue; }

  # 이미 UTF-8(또는 ASCII)이면 스킵
  if iconv -f utf-8 -t utf-8 "$file" >/dev/null 2>&1; then
    rm -f "$tmp"
    # echo "Skip (UTF-8): $file"
    continue
  fi

  echo "Converting '$file' (cp949 → utf-8)..."
  if iconv -f cp949 -t utf-8 "$file" > "$tmp" 2>/dev/null; then
    touch -r "$file" "$tmp"   # 수정시간 보존
    mv "$tmp" "$file"
    echo "Converted successfully."
  else
    rm -f "$tmp"
    echo "Conversion failed for '$file'. Skipping."
  fi
done
