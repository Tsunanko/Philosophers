#!/bin/bash
# このスクリプトは、すべての.cファイルに#include "philo.h"があるかチェックします

FILES="sim.c monitor.c print.c state.c launch.c routine.c parse.c time_utils.c main.c"

for file in $FILES; do
    if [ -f "$file" ]; then
        if ! grep -q '^#include "philo.h"' "$file"; then
            echo "ERROR: $file に #include \"philo.h\" がありません"
            exit 1
        fi
    fi
done

echo "✓ すべてのファイルに #include \"philo.h\" が含まれています"
exit 0

