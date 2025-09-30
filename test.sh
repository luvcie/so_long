RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "======================================"
echo "     SO_LONG VALIDATION TESTS"
echo "======================================"

total=0
passed=0

run_test() {
    total=$((total + 1))
    test_name=$1
    command=$2
    expected=$3
    
    echo -n "Test $total: $test_name... "
    output=$(eval "$command" 2>&1)
    
    if echo "$output" | grep -q "$expected"; then
        echo -e "${GREEN}PASS${NC}"
        passed=$((passed + 1))
    else
        echo -e "${RED}FAIL${NC}"
        echo "  Expected: $expected"
        echo "  Got: $output"
    fi
}

echo ""
echo "=== EXTENSION VALIDATION ==="
run_test "Non-.ber file (.txt)" "./so_long maps/test.txt" "File must have .ber extension"
run_test "Non-.ber file (.mp3)" "./so_long maps/test.mp3" "File must have .ber extension"
run_test "Non-.ber file (.a)" "./so_long maps/i.a" "File must have .ber extension"
run_test "Short filename" "./so_long a.b" "Invalid file name"

echo ""
echo "=== MAP STRUCTURE VALIDATION ==="
run_test "No walls" "./so_long maps/nowalls.ber" "Map must be surrounded by walls"
run_test "Not rectangular" "./so_long maps/notrectangle.ber" "Map must be rectangular"

echo ""
echo "=== ELEMENT VALIDATION ==="
run_test "No player" "./so_long maps/noplayer.ber" "Map must have exactly 1 player"
run_test "Two players" "./so_long maps/twoplayers.ber" "Map must have exactly 1 player"
run_test "No exit" "./so_long maps/noexit.ber" "Map must have exactly 1 exit"
run_test "No collectibles" "./so_long maps/nocollectibles.ber" "Map must have at least 1 collectible"
run_test "Invalid character" "./so_long maps/invalidchar.ber" "Invalid character in map"

echo ""
echo "=== VALID MAP TEST ==="
echo -n "Test $((total + 1)): Valid map loads... "
timeout 2 ./so_long maps/apartment.ber &
pid=$!
sleep 1
if ps -p $pid > /dev/null; then
    echo -e "${GREEN}PASS${NC} (window opened)"
    kill $pid 2>/dev/null
    total=$((total + 1))
    passed=$((passed + 1))
else
    echo -e "${RED}FAIL${NC}"
    total=$((total + 1))
fi

echo ""
echo "======================================"
echo "      RESULTS: $passed/$total PASSED"
echo "======================================"

if [ $passed -eq $total ]; then
    echo -e "${GREEN}All tests passed! Ready for evaluation.${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed. Check your validation.${NC}"
    exit 1
fi
