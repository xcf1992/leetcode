import java.util.*;

class FileSystem {
    private TrieNode root;

    public FileSystem() {
        this.root = new TrieNode();
    }

    public List<String> ls(String path) {
        String[] nodes = path.split("/");
        int len = nodes.length;
        TrieNode cur = root;
        List<String> result = new ArrayList<>();
        for (int i = 1; i < len; ++i) {
            cur = cur.child.get(nodes[i]);
        }

        if (cur.isFile) {
            result.add(nodes[len - 1]);
            return result;
        }
        result.addAll(cur.child.keySet());
        Collections.sort(result);
        return result;
    }

    public void mkdir(String path) {
        String[] nodes = path.split("/");
        int len = nodes.length;
        TrieNode cur = root;
        for (int i = 1; i < len; ++i) {
            if (!cur.child.containsKey(nodes[i])) {
                cur.child.put(nodes[i], new TrieNode());
            }
            cur = cur.child.get(nodes[i]);
        }
    }

    public void addContentToFile(String filePath, String content) {
        String[] nodes = filePath.split("/");
        int len = nodes.length;
        TrieNode cur = root;
        for (int i = 1; i < len; ++i) {
            if (!cur.child.containsKey(nodes[i])) {
                cur.child.put(nodes[i], new TrieNode());
            }
            cur = cur.child.get(nodes[i]);
        }
        cur.isFile = true;
        cur.content += content;
    }

    public String readContentFromFile(String filePath) {
        String[] nodes = filePath.split("/");
        int len = nodes.length;
        TrieNode cur = root;
        for (int i = 1; i < len; ++i) {
            cur = cur.child.get(nodes[i]);
        }
        return cur.content;
    }

    public class TrieNode {
        public boolean isFile;
        public Map<String, TrieNode> child;
        public String content;

        public TrieNode() {
            this.isFile = false;
            this.child = new HashMap<>();
            this.content = "";
        }
    }
}
