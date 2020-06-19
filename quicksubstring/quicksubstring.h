#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace qs {
    using namespace std;

	class ProcessingUnit {
	public:
		ProcessingUnit(string base_string_, char delim_ = '$') {
            base_string = base_string_;
            n = base_string_.size();
            delim = delim_;

            c.resize(n);
            p.resize(n);

            BuildPrefixArray();
        }

        ProcessingUnit() {}

		void SetDelim(char delim_) {
			delim = delim_;
			if (initialized) {
				BuildPrefixArray();
			}
		}

        bool Substr(const std::string& substring) {
            int ns = substring.size();
            int l = 0, r = n - 1;
            while (l <= r) {
                int mid = l + (r - l) / 2;

                if (base_string.substr(p[mid], ns) == substring) {
                    return true;
                }

                if (base_string.substr(p[mid], ns) < substring)
                    l = mid + 1;
                else
                    r = mid - 1;
            }

            return false;
        }

	private:

        void dsort(vector<pair<pair<int, int>, int>>& a) {
            int n = a.size();

            vector<pair<pair<int, int>, int>> b(n);

            {
                vector<int> cnt(n);
                for (auto x : a) {
                    cnt[x.first.second]++;
                }

                vector<int> pos(n);
                for (int i = 1; i < n; i++) {
                    pos[i] = pos[i - 1] + cnt[i - 1];
                }

                for (auto x : a) {
                    b[pos[x.first.second]] = x;
                    pos[x.first.second]++;
                }
            }

            {
                vector<int> cnt(n);
                for (auto x : a) {
                    cnt[x.first.first]++;
                }

                vector<int> pos(n);
                for (int i = 1; i < n; i++) {
                    pos[i] = pos[i - 1] + cnt[i - 1];
                }

                for (auto x : b) {
                    a[pos[x.first.first]] = x;
                    pos[x.first.first]++;
                }
            }
        }

		void BuildPrefixArray() {

            base_string += delim;

            {
                std::vector<std::pair<char, int>> a(n);
                for (int i = 0; i < n; i++) a[i] = { base_string[i], i };
                sort(begin(a), end(a));

                for (int i = 0; i < n; i++) p[i] = a[i].second;

                c[p[0]] = 0;
                for (int i = 1; i < n; i++) {
                    if (a[i].first == a[i - 1].first)
                        c[p[i]] = c[p[i - 1]];
                    else
                        c[p[i]] = c[p[i - 1]] + 1;
                }
            }

            for (int k = 0; (1 << k) < n; k++) {
                vector<pair<pair<int, int>, int>> a(n);
                for (int i = 0; i < n; i++)
                    a[i] = { {c[i], c[(i + (1 << k)) % n]}, i };

                dsort(a);

                for (int i = 0; i < n; i++) p[i] = a[i].second;

                c[p[0]] = 0;
                for (int i = 1; i < n; i++) {
                    if (a[i].first == a[i - 1].first)
                        c[p[i]] = c[p[i - 1]];
                    else
                        c[p[i]] = c[p[i - 1]] + 1;
                }
            }

			initialized = true;
		}

		std::string base_string;
		char delim = '$';
		bool initialized = false;
        int n = 0;
        vector<int> p, c;
	};
}