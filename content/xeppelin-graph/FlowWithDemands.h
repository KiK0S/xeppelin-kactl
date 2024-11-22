/**
 * Author: kik0s
 * Date: 2024-11-16
 * Description: Flow with demands $d(e) \le f(e) \le c(e)$. Add new source $s'$ and sink $t'$ to the graph.
 * \begin{itemize}
 * \item $c'((s', v)) = \sum_{u \in V} d((u, v))$ for each edge $(s', v)$.
 * \item $c'((v, t')) = \sum_{w \in V} d((v, w))$ for each edge $(v, t')$.
 * \item $c'((u, v)) = c((u, v)) - d((u, v))$ for each edge $(u, v)$ in the old network.
 * \item $c'((t, s)) = \infty$
 * \end{itemize}
 * A flow with the value $d(e)$, that originally flowed along the path $s - \dots - u - v - \dots t$ can now take the new path $s' - v - \dots - t - s - \dots - u - t'$.
 * Status: works
 */
