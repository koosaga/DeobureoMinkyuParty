#include <bits/stdc++.h>
using namespace std;
using lint = long long;

namespace FIO{
	static char buf[1 << 19]; // size : any number geq than 1024
	static int idx = 0;
	static int bytes = 0;
	static inline int _read() {
		if (!bytes || idx == bytes) {
			bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
			idx = 0;
		}
		return buf[idx++];
	}
	static inline int _readInt() {
		int x = 0, s = 1;
		int c = _read();
		while (c <= 32) c = _read();
		if (c == '-') s = -1, c = _read();
		while (c > 32) x = 10 * x + (c - '0'), c = _read();
		if (s < 0) x = -x;
		return x;
	}
}

namespace fft{
	void fft(vector<lint> &a, bool inv){
		int n = a.size(), j = 0;
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		for(int i=2; i<=n; i<<=1){
			int step = n / i;
			for(int j=0; j<n; j+=i){
				for(int k=0; k<i/2; k++){
					lint u = a[j+k];
					lint v = a[j+k+i/2];
					if(!inv){
						a[j+k] = v;
						a[j+k+i/2] = u+v;
					}
					else{
						a[j+k] = v-u;
						a[j+k+i/2] = u;
					}
				}
			}
		}
	}
	vector<lint> multiply(vector<lint> v, vector<lint> w){
		vector<lint> fv(v.begin(), v.end());
		vector<lint> fw(w.begin(), w.end());
		int n = 2;
		while(n < v.size() + w.size()) n <<= 1;
		fv.resize(n); fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		return fv;
	}
}

vector<lint> or_convolution(vector<lint> a, vector<lint> b){
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	vector<lint> d = fft::multiply(a, b);
	d.resize(a.size());
	reverse(d.begin(), d.end());
	return d;
}

int n, pwr[20];
int a[600000], b[600000];
lint dap[600000];

vector<int> tov(int w){
	vector<int> v;
	for(int i=0; i<n; i++){
		v.push_back(w % 3);
		w /= 3;
	}
	return v;
}

lint prec[1<<24];
vector<int> dseq;

lint bktk(int pos, int msk){
	if(pos == n) return prec[msk];
	lint ret = 0;
	if(dseq[pos] >= 2){
		ret += bktk(pos + 1, msk + (2<<(2*pos)));
		ret += bktk(pos + 1, msk + (3<<(2*pos)));
	}
	else{
		ret += bktk(pos + 1, msk + (dseq[pos] << (2 * pos)));
	}
	return ret;
}



int op[20];
lint aux1[1<<12];
lint aux2[1<<12];
lint precA[600000];
lint precB[600000];

void precalculate(){
	for(int i=0; i<pwr[n]; i++) precA[i] = a[i], precB[i] = b[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<pwr[n]; j++){
			int modv = j % pwr[i + 1];
			modv /= pwr[i];
			if(modv == 2){
				precA[j] += precA[j - pwr[i]];
				precB[j] += precB[j - pwr[i]];
			}
		}
	}
}

void dfs2(int pos, int idx = 0, int msk = 0, int cnt = 0){
	if(pos == n) aux2[msk] += precB[idx];
	else{
		if(op[pos] == 1) dfs2(pos + 1, idx + pwr[pos], msk, cnt);
		if(op[pos] == 2) dfs2(pos + 1, idx, msk, cnt);
		if(op[pos] == 0){
			dfs2(pos + 1, idx, msk | (1<<cnt), cnt + 1);
			dfs2(pos + 1, idx + 2 * pwr[pos], msk, cnt + 1);
		}
	}
}

void dfs1(int pos, int idx = 0, int msk = 0, int cnt = 0){
	if(pos == n) aux1[msk] += precA[idx];
	else{
		if(op[pos] == 1) dfs1(pos + 1, idx, msk, cnt);
		if(op[pos] == 2) dfs1(pos + 1, idx + pwr[pos], msk, cnt);
		if(op[pos] == 0){
			dfs1(pos + 1, idx, msk | (1<<cnt), cnt + 1);
			dfs1(pos + 1, idx + 2 * pwr[pos], msk, cnt + 1);
		}
	}
}
int main(){
	n = FIO::_readInt();
	pwr[0] = 1;
	for(int i=1; i<=n; i++) pwr[i] = pwr[i-1] * 3;
	for(int i=0; i<pwr[n]; i++) a[i] = FIO::_readInt();
	for(int i=0; i<pwr[n]; i++) b[i] = FIO::_readInt();
	precalculate();
	for(int i=0; i<(1<<n); i++){
		vector<int> l, r;
		for(int j=0; j<n; j++){
			if((i >> j) & 1) l.push_back(j);
			else r.push_back(j);
		}
		for(int j=0; j<(1<<l.size()); j++){
			memset(op, 0, sizeof(op));
			int rsz = n - l.size();
			int temp_idx = 0;
			for(int k=0; k<l.size(); k++){
				if((j >> k) & 1){
					op[l[k]] = 2;
					temp_idx += (3 << (2 * l[k]));
				}
				else{
					op[l[k]] = 1;
					temp_idx += (2 << (2 * l[k]));
				}
			}
			memset(aux1, 0, sizeof(lint) * (1 << rsz));
			memset(aux2, 0, sizeof(lint) * (1 << rsz));
			dfs1(0);
			dfs2(0);
			vector<lint> sol1(aux1, aux1 + (1<<rsz));
			vector<lint> sol2(aux2, aux2 + (1<<rsz));
			auto conv = or_convolution(sol1, sol2);
			for(int k=0; k<(1<<rsz); k++){
				int neo_idx = temp_idx;
				for(int l=0; l<rsz; l++){
					if((k >> l) & 1) neo_idx += (1 << (2 * r[l]));
				}
				prec[neo_idx] += conv[k];
			}
		}
	}
	for(int i=0; i<(1<<n); i++){
		vector<int> v;
		for(int j=0; j<n; j++){
			if((i >> j) & 1) v.push_back(j);
		}
		vector<lint> ans;
		for(int j=0; j<(1<<v.size()); j++){
			vector<int> seq(n, 0);
			for(int k=0; k<v.size(); k++){
				if((j >> k) & 1) seq[v[k]] = 2;
				else seq[v[k]] = 1;
			}
			dseq = seq;
			ans.push_back(bktk(0, 0));
		}
		for(int i=ans.size()-1; i>=0; i--){
			for(int j=i; j; j=(j-1)&i){
				ans[i^j] -= ans[i];
			}
		}
		for(int j=0; j<ans.size(); j++){
			int idx = 0;
			for(int k=0; k<v.size(); k++){
				if((j >> k) & 1){
					idx += 2 * pwr[v[k]];
				}
				else idx += pwr[v[k]];
			}
			dap[idx] += ans[j];
		}
	}
	for(int i=0; i<pwr[n]; i++){
		printf("%lld ", dap[i]);
	}
}
