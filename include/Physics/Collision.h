#pragma once

#include <Physics/Rect.h>
#include <Physics/Vec2.h>
#include <algorithm>
#include <cmath>

class Collision {
	public:
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			Vec2 A[] = { Vec2( a.x, a.y + a.h ),
						  Vec2( a.x + a.w, a.y + a.h ),
						  Vec2( a.x + a.w, a.y ),
						  Vec2( a.x, a.y )
						};
			Vec2 B[] = { Vec2( b.x, b.y + b.h ),
						  Vec2( b.x + b.w, b.y + b.h ),
						  Vec2( b.x + b.w, b.y ),
						  Vec2( b.x, b.y )
						};

			for (auto& v : A) {
				v = (v - a.GetCenter()).Rotate(angleOfA) + a.GetCenter();
			}

			for (auto& v : B) {
				v = (v - b.GetCenter()).Rotate(angleOfB) + b.GetCenter();
			}

			Vec2 axes[] = { (A[0] - A[1]).Normalize(), (A[1] - A[2]).Normalize(), (B[0] - B[1]).Normalize(), (B[1] - B[2]).Normalize() };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = A[i].Dot(axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = B[i].Dot(axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}

		static inline Vec2* GetMTV(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			Vec2 A[] = { Vec2( a.x, a.y + a.h ),
										Vec2( a.x + a.w, a.y + a.h ),
										Vec2( a.x + a.w, a.y ),
										Vec2( a.x, a.y )
									};
			Vec2 B[] = { Vec2( b.x, b.y + b.h ),
										Vec2( b.x + b.w, b.y + b.h ),
										Vec2( b.x + b.w, b.y ),
										Vec2( b.x, b.y )
									};

			for (auto& v : A) {
					v = (v - a.GetCenter()).Rotate(angleOfA) + a.GetCenter();
			}

			for (auto& v : B) {
					v = (v - b.GetCenter()).Rotate(angleOfB) + b.GetCenter();
			}

			Vec2 axes[] = { (A[0] - A[1]).Normalize(), (A[1] - A[2]).Normalize(), (B[0] - B[1]).Normalize(), (B[1] - B[2]).Normalize() };

			float minOverlap = std::numeric_limits<float>::infinity();
			Vec2 minAxis(0.0f, 0.0f);

			// vetor do centro de A para o centro de B (usado para orientar o eixo)
			Vec2 centerDir = b.GetCenter() - a.GetCenter();

			for (auto axis : axes) {
					float P[4];

					for (int i = 0; i < 4; ++i) P[i] = A[i].Dot(axis);

					float minA = *std::min_element(P, P + 4);
					float maxA = *std::max_element(P, P + 4);

					for (int i = 0; i < 4; ++i) P[i] = B[i].Dot(axis);

					float minB = *std::min_element(P, P + 4);
					float maxB = *std::max_element(P, P + 4);

					// Separating axis?
					if (maxA < minB || minA > maxB)
							return nullptr;

					// overlap entre as projeções
					float overlap = std::min(maxA, maxB) - std::max(minA, minB);

					if (overlap < minOverlap) {
							minOverlap = overlap;
							minAxis = axis;
							// garantir que minAxis aponte de A para B
							if (centerDir.Dot(minAxis) < 0.0f) minAxis = minAxis * -1.0f;
					}
			}

			Vec2* outCollisionDir = new Vec2();

			// normalizado: direção da colisão (do centro de A para centro de B pelo eixo de menor penetração)
			*outCollisionDir = minAxis.Normalize() * minOverlap * -1.0f;
			return outCollisionDir;
	}
};
