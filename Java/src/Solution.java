import java.util.Arrays;
import java.util.List;

public class Solution {
    private static FileSystem fileSystem = new FileSystem();

    public static void main(String[] args) {
        List<Integer> vec1 = Arrays.asList(1, 2, 3);
        List<Integer> vec2 = Arrays.asList(4,5,6);
        List<List<Integer>> vec2d = Arrays.asList(vec1, vec2);

        Vector2D vector2D = new Vector2D(vec2d);
        while (vector2D.hasNext()) {
            System.out.println(vector2D.next());
        }
    }
}
